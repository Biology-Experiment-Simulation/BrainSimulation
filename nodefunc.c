/**
 * Represents the behavior of single nodes.
 */
#include "nodefunc.h"

nodestate_t process(nodeval_t act_old, nodeval_t slope_old, int number_d_neighbors, nodeval_t *d_neighbors,
                  int number_id_neighbors, nodeval_t *id_neighbors){
    // calculate mean over all madn nodes
    nodeval_t madn = 0;
    for (int i = 0; i < number_d_neighbors; ++i) {
        madn = madn + d_neighbors[i];
    }
    madn = madn/number_d_neighbors;

    // calculate mean over all maidn nodes
    nodeval_t maidn = 0;
    for (int i = 0; i < number_id_neighbors; ++i) {
        maidn = maidn + id_neighbors[i];
    }
    maidn = maidn/number_id_neighbors;


    // rest of the algorithm
    nodeval_t slope3 = madn - slope_old;
    nodeval_t slope4 = maidn - slope_old;
    nodeval_t slope_vector = slope3 + slope4;
    nodeval_t slope_new = slope_old + slope_vector;
    nodeval_t act_new = act_old + slope_new;

    // physical damping
    double damping = 0.2;
    act_new = act_new/(1+damping);

    nodestate_t res;
    res.act = act_new;
    res.slope = slope_new;

    return res;
}