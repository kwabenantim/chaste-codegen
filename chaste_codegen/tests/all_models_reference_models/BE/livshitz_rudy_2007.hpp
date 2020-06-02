#ifndef CELLLIVSHITZ_RUDY_2007FROMCELLMLBACKWARDEULER_HPP_
#define CELLLIVSHITZ_RUDY_2007FROMCELLMLBACKWARDEULER_HPP_

//! @file
//!
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//!
//! Model: LivshitzRudy2007
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen)
//! on (date omitted as unimportant)
//!
//! <autogenerated>

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>
#include "AbstractStimulusFunction.hpp"
#include "AbstractBackwardEulerCardiacCell.hpp"

class Celllivshitz_rudy_2007FromCellMLBackwardEuler : public AbstractBackwardEulerCardiacCell<7>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractBackwardEulerCardiacCell<7> >(*this);
        
    }

    //
    // Settable parameters and readable variables
    //

public:

    boost::shared_ptr<RegularStimulus> UseCellMLDefaultStimulus();
    Celllivshitz_rudy_2007FromCellMLBackwardEuler(boost::shared_ptr<AbstractIvpOdeSolver> /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus);
    ~Celllivshitz_rudy_2007FromCellMLBackwardEuler();
    double GetIIonic(const std::vector<double>* pStateVariables=NULL);void ComputeResidual(double var_chaste_interface__Environment__time, const double rCurrentGuess[7], double rResidual[7]);
    void ComputeJacobian(double var_chaste_interface__Environment__time, const double rCurrentGuess[7], double rJacobian[7][7]);protected:
    void UpdateTransmembranePotential(double var_chaste_interface__Environment__time);
    void ComputeOneStepExceptVoltage(double var_chaste_interface__Environment__time);

    std::vector<double> ComputeDerivedQuantities(double var_chaste_interface__Environment__time, const std::vector<double> & rY);
};

// Needs to be included last
#include "SerializationExportWrapper.hpp"
CHASTE_CLASS_EXPORT(Celllivshitz_rudy_2007FromCellMLBackwardEuler)

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        inline void save_construct_data(
            Archive & ar, const Celllivshitz_rudy_2007FromCellMLBackwardEuler * t, const unsigned int fileVersion)
        {
            const boost::shared_ptr<AbstractIvpOdeSolver> p_solver = t->GetSolver();
            const boost::shared_ptr<AbstractStimulusFunction> p_stimulus = t->GetStimulusFunction();
            ar << p_solver;
            ar << p_stimulus;
        }

        template<class Archive>
        inline void load_construct_data(
            Archive & ar, Celllivshitz_rudy_2007FromCellMLBackwardEuler * t, const unsigned int fileVersion)
        {
            boost::shared_ptr<AbstractIvpOdeSolver> p_solver;
            boost::shared_ptr<AbstractStimulusFunction> p_stimulus;
            ar >> p_solver;
            ar >> p_stimulus;
            ::new(t)Celllivshitz_rudy_2007FromCellMLBackwardEuler(p_solver, p_stimulus);
        }

    }

}

#endif // CELLLIVSHITZ_RUDY_2007FROMCELLMLBACKWARDEULER_HPP_