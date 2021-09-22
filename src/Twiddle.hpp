#ifndef TWIDDLE_H
#define TWIDDLE_H
#include <vector>

class TWIDDLE
{
public:
    /**
   * Constructor
   */
    TWIDDLE(double tolerance, std::vector<double> init_params);

    /**
   * Destructor.
   */
    virtual ~TWIDDLE();

    void Run();

    void SetError(const double cte);

    std::vector<double> GetParams();

    bool DoneTwiddle();

private:

    enum States
    {
        START,
        FIRST_RUN,
        INCREMENT,
        DECREMENT,
        DONE
    };

    double curr_error;
    double best_error;
    double tolerance;

    unsigned int inter;
    unsigned int  num_interactions;
    

    States curr_state;
    unsigned int param_index;
    
    
    std::vector<double> params;
    std::vector<double> d_params;

    

    void ChangeParamIndex();
};

#endif // TWIDDLE_H