#
# Shared classes and methods for testing.
#
import io
import os
import sys
import shutil
import tempfile


class StreamCapture(object):
    """
    A context manager that redirects and captures the output stdout, stderr,
    or both.
    """
    # This class was taken from Pints: https://github.com/pints-team/pints

    def __init__(self, stdout=True, stderr=False):
        super(StreamCapture, self).__init__()

        # True if currently capturing
        self._capturing = False

        # Settings
        self._stdout_enabled = True if stdout else False
        self._stderr_enabled = True if stderr else False

        # Captured output
        self._stdout_captured = None
        self._stderr_captured = None

        # Original streams
        self._stdout_original = None
        self._stderr_original = None

        # Buffers to redirect to
        self._stdout_buffer = None
        self._stderr_buffer = None

    def __enter__(self):
        """ Called when the context is entered. """
        self._start_capturing()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        """ Called when exiting the context. """
        self._stop_capturing()

    def _start_capturing(self):
        """ Starts capturing output. """
        if self._capturing:
            return
        self._capturing = True

        # stdout
        if self._stdout_enabled:

            # Create buffer
            self._stdout_buffer = io.StringIO()

            # Save current stream
            self._stdout_original = sys.stdout

            # If possible, flush current output stream
            try:
                self._stdout_original.flush()
            except AttributeError:
                pass

            # Redirect
            sys.stdout = self._stdout_buffer

        # stderr
        if self._stderr_enabled:

            # Create buffer
            self._stderr_buffer = io.StringIO()

            # Save current stream
            self._stderr_original = sys.stderr

            # If possible, flush current output stream
            try:
                self._stderr_original.flush()
            except AttributeError:
                pass

            # Redirect
            sys.stderr = self._stderr_buffer

    def _stop_capturing(self):
        """ Stops capturing output. """
        if not self._capturing:
            return

        # stdout
        if self._stdout_enabled:
            self._stdout_buffer.flush()
            sys.stdout = self._stdout_original
            self._stdout_captured = self._stdout_buffer.getvalue()
            self._stdout_buffer = None

        # stderr
        if self._stderr_enabled:
            self._stderr_buffer.flush()
            sys.stderr = self._stderr_original
            self._stderr_captured = self._stderr_buffer.getvalue()
            self._stderr_buffer = None

        self._capturing = False

    def text(self):
        """
        Disables capturing and returns the captured text.

        If only ``stdout`` or ``stderr`` was enabled, a single string is
        returned. If both were enabled a tuple of strings is returned.
        """
        self._stop_capturing()
        if self._stdout_enabled:
            if self._stderr_enabled:
                return self._stdout_captured, self._stderr_captured
            return self._stdout_captured
        return self._stderr_captured    # Could be None

