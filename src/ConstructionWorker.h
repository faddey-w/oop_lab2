#ifndef CONSTRUCTIONWORKER_H
#define CONSTRUCTIONWORKER_H

#include <string>
#include <exception>


class ConstructionWorker {
public:

    enum State {WORK, REST};
    static const unsigned MIN_REST_TIME = 15;
    static const unsigned MAX_BRICKS_BETWEEN_REST = 20;

    ConstructionWorker();

    void go_work();
    void go_rest();
    void rest(unsigned minutes);
    void lay_bricks(unsigned n_bricks);

    unsigned bricks_laid() const;
    unsigned minutes_rested() const;
    State get_state() const;

private:
    State state;
    unsigned counter;
};

#endif // CONSTRUCTIONWORKER_H
