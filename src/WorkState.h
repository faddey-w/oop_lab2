//
// Created by faddey on 04.12.16.
//

#ifndef LAB2_WORKSTATE_H
#define LAB2_WORKSTATE_H

#include "ConstructionWorker.hpp"


class WorkState: public IWorkerState {
    unsigned n_bricks_laid = 0;
public:

    IWorkerState* go_work();
    IWorkerState* go_rest();

    void rest(unsigned minutes);
    void lay_bricks(unsigned n_bricks);

    unsigned bricks_laid() const;
    unsigned minutes_rested() const;
    ConstructionWorker::State get_state_id() const;
};


#endif //LAB2_WORKSTATE_H
