#ifndef CELLFINK_NOBLE_GILES_MODEL_2008FROMCELLML_HPP_
#define CELLFINK_NOBLE_GILES_MODEL_2008FROMCELLML_HPP_

//! @file
//! 
//! This source file was generated from CellML.
//! 
//! Model: fink_noble_giles_model_2008
//! 
//! Processed by weblab_cg: https://github.com/ModellingWebLab/weblab-cg
//!     (translator: weblab_cg, model type: normal, options: )
//! on 2019-12-06 12:05:34
//! 
//! <autogenerated>

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>
#include "AbstractCardiacCell.hpp"

#include "AbstractStimulusFunction.hpp"

class Cellfink_noble_giles_model_2008FromCellML : public AbstractCardiacCell
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractCardiacCell >(*this);
        
    }
    
    // 
    // Settable parameters and readable variables
    // 
    
public:
    boost::shared_ptr<RegularStimulus> UseCellMLDefaultStimulus();
    Cellfink_noble_giles_model_2008FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus);
    ~Cellfink_noble_giles_model_2008FromCellML();
    double GetIIonic(const std::vector<double>* pStateVariables=NULL);
    void EvaluateYDerivatives(double var_chaste_interface__Environment__time, const std::vector<double>& rY, std::vector<double>& rDY);
};


// Needs to be included last
#include "SerializationExportWrapper.hpp"
CHASTE_CLASS_EXPORT(Cellfink_noble_giles_model_2008FromCellML)

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        inline void save_construct_data(
            Archive & ar, const Cellfink_noble_giles_model_2008FromCellML * t, const unsigned int fileVersion)
        {
            const boost::shared_ptr<AbstractIvpOdeSolver> p_solver = t->GetSolver();
            const boost::shared_ptr<AbstractStimulusFunction> p_stimulus = t->GetStimulusFunction();
            ar << p_solver;
            ar << p_stimulus;
        }
        
        template<class Archive>
        inline void load_construct_data(
            Archive & ar, Cellfink_noble_giles_model_2008FromCellML * t, const unsigned int fileVersion)
        {
            boost::shared_ptr<AbstractIvpOdeSolver> p_solver;
            boost::shared_ptr<AbstractStimulusFunction> p_stimulus;
            ar >> p_solver;
            ar >> p_stimulus;
            ::new(t)Cellfink_noble_giles_model_2008FromCellML(p_solver, p_stimulus);
        }
        
    }
    
}

#endif // CELLFINK_NOBLE_GILES_MODEL_2008FROMCELLML_HPP_