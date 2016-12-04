
#ifndef LAB2_RESTSTATE_H
#define LAB2_RESTSTATE_H

#include "ConstructionWorker.hpp"


class RestState: public IWorkerState {

    unsigned n_minutes_rested = 0;

public:
    IWorkerState* go_work();
    IWorkerState* go_rest();

    void rest(unsigned minutes);
    void lay_bricks(unsigned n_bricks);

    unsigned bricks_laid() const;
    unsigned minutes_rested() const;
    ConstructionWorker::State get_state_id() const;
};


#endif //LAB2_RESTSTATE_H
