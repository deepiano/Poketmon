#include "selectalgorithm.h"

SelectAlgorithm::SelectAlgorithm()
{

}

void SelectAlgorithm::SetGraph(GraphType *gr)
{
    g=gr;
}
int SelectAlgorithm::getAlgnum()
{
    return algNum;
}
