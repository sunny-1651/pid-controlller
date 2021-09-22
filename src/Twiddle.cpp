#include "Twiddle.hpp"
#include <vector>
#include <numeric>
#include <iostream>

TWIDDLE::TWIDDLE(double tolerance, std::vector<double> init_params) 
    :   tolerance(tolerance),
        curr_state(START),
        param_index(0),
        num_interactions(5000),
        inter(0),
        params({ init_params[0], init_params[1], init_params[2] }),
        d_params({ 1.0, 1.0, 1.0 })
    {}

TWIDDLE::~TWIDDLE() {}

void TWIDDLE::Run()
{
    double sum_dp = 0.0;
    for(auto& n : d_params) {
        sum_dp += n;
    }

    if(sum_dp < tolerance){
        curr_state = DONE;
    }

    switch (curr_state)
    {
    case START:
        params = { 0.0, 0.0, 0.0 };
        d_params = { 1.0, 1.0, 1.0 };
        curr_state = FIRST_RUN;
        break;
    case FIRST_RUN:
        best_error = curr_error;
        params[param_index] += d_params[param_index];
        curr_state = INCREMENT;
        break;
    case INCREMENT:
        if (curr_error < best_error){
            best_error = curr_error;
            d_params[param_index] *= 1.1;
            ChangeParamIndex();
            params[param_index] += d_params[param_index];
        }
        else {
            params[param_index] -= 2 * d_params[param_index];
            curr_state = DECREMENT;
        }
        break;
    case DECREMENT:
        if(curr_error < best_error){
            best_error = curr_error;
            d_params[param_index] *= 1.1;
        }
        else {
            params[param_index] += d_params[param_index];
            d_params[param_index] *= 0.9;
        }
        curr_state = INCREMENT;
        ChangeParamIndex();
        params[param_index] += d_params[param_index];
        break;
    case DONE:
        //Do nothing
        break;
    default:
        break;
    }

    std::cout << "Kp: " << params[0] << " Ki: " << params[1] << " Kd: " << params[2] << std::endl;
}

void TWIDDLE::SetError(const double cte){
    curr_error = cte;
}

std::vector<double> TWIDDLE::GetParams(){
    return params;
}

void TWIDDLE::ChangeParamIndex(){
    param_index = (param_index + 1) % params.size();
}

bool TWIDDLE::DoneTwiddle(){
    inter++;
    return (inter >= num_interactions);
}
