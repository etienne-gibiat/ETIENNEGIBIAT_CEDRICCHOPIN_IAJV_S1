#include "Evaluate.h"

float Evaluate::Eval_Ressources(Ressource ressource, World& world) const
{
    const auto iter = world.Stock.find(ressource);
    if (iter != world.Stock.end()) {
        float eval = std::max((static_cast<float>(iter->second.second) - iter->second.first) / iter->second.second, 0.0f);
        
        return  eval;
    }
    return 0.0f;
}

float Evaluate::EvaluationTimeIdle(const float time) const
{
    float eval = std::max(exp2f(-0.1 * time), static_cast <float>(0.0));
    std::cout << "eval timeidle : " << eval << std::endl;
    return eval;
}

float Evaluate::EvaluationCreationHabitantNombre(const World& world) const
{
    float eval = exp2f(-2 * (world.nbHabitant / static_cast<float>(world.nbHabitantDesired)));
    std::cout << "Evaluation habitant en fonction du nombre : " << eval << std::endl;
    return eval;
}

float Evaluate::Eval_MoyCreationHabitant(const float time, Ressource ressource, World& world) const
{
    float moy = 0;
    float evalRessource = Eval_Ressources(ressource, world);
    float evalIdle = EvaluationTimeIdle(time);
    float evalCreation = EvaluationCreationHabitantNombre(world);

    moy = (evalRessource + evalIdle + evalCreation) / 3.0f;
    std::cout << "Besoin pour la creation d'un habitant (actuel : " << world.nbHabitant << " ) : " << moy << std::endl;
    return moy;
}
