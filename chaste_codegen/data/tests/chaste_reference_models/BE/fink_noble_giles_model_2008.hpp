#ifndef DYNAMICFINK_NOBLE_GILES_MODEL_2008FROMCELLMLBACKWARDEULER_HPP_
#define DYNAMICFINK_NOBLE_GILES_MODEL_2008FROMCELLMLBACKWARDEULER_HPP_

//! @file
//! 
//! This source file was generated from CellML.
//! 
//! Model: fink_noble_giles_model_2008
//! 
//! Processed by pycml - CellML Tools in Python
//!     (translators: , pycml: , optimize: )
//! on Wed Mar 11 16:46:40 2020
//! 
//! <autogenerated>

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>
#include "AbstractBackwardEulerCardiacCell.hpp"
#include "AbstractDynamicallyLoadableEntity.hpp"
#include "AbstractStimulusFunction.hpp"

class Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler : public AbstractBackwardEulerCardiacCell<17>, public AbstractDynamicallyLoadableEntity
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractBackwardEulerCardiacCell<17> >(*this);
        archive & boost::serialization::base_object<AbstractDynamicallyLoadableEntity>(*this);
    }
    
    // 
    // Settable parameters and readable variables
    // 
    
public:
    boost::shared_ptr<RegularStimulus> UseCellMLDefaultStimulus();
    Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler(boost::shared_ptr<AbstractIvpOdeSolver> /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus);
    ~Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler();
    double GetIIonic(const std::vector<double>* pStateVariables=NULL);
    void ComputeResidual(double var_chaste_interface__Environment__time, const double rCurrentGuess[17], double rResidual[17]);
    void ComputeJacobian(double var_chaste_interface__Environment__time, const double rCurrentGuess[17], double rJacobian[17][17]);
protected:
    void UpdateTransmembranePotential(double var_chaste_interface__Environment__time);
    void ComputeOneStepExceptVoltage(double var_chaste_interface__Environment__time);
};


// Needs to be included last
#include "SerializationExportWrapper.hpp"
CHASTE_CLASS_EXPORT(Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler)

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        inline void save_construct_data(
            Archive & ar, const Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler * t, const unsigned int fileVersion)
        {
            const boost::shared_ptr<AbstractIvpOdeSolver> p_solver = t->GetSolver();
            const boost::shared_ptr<AbstractStimulusFunction> p_stimulus = t->GetStimulusFunction();
            ar << p_solver;
            ar << p_stimulus;
        }
        
        template<class Archive>
        inline void load_construct_data(
            Archive & ar, Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler * t, const unsigned int fileVersion)
        {
            boost::shared_ptr<AbstractIvpOdeSolver> p_solver;
            boost::shared_ptr<AbstractStimulusFunction> p_stimulus;
            ar >> p_solver;
            ar >> p_stimulus;
            ::new(t)Dynamicfink_noble_giles_model_2008FromCellMLBackwardEuler(p_solver, p_stimulus);
        }
        
    }
    
}

#endif // DYNAMICFINK_NOBLE_GILES_MODEL_2008FROMCELLMLBACKWARDEULER_HPP_
