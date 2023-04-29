//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_METHODS_H
#define UFCITY_METHODS_H

namespace methods{

    static const char NONE                  = 'A';

    /* data aggregation */
    static const char FIXED_SIZE            = 'B';
    static const char HAPPENS_FIRST         = 'C';
    static const char FIXED_TIME            = 'D';

    /* missing data */
    static const char MEAN_METHOD           = 'E';
    static const char MEDIAN_METHOD         = 'F';
    static const char LOCF_METHOD           = 'G'; /* Last Observation Carried Forward  */
    static const char INTERPOLATION_METHOD  = 'H';
    static const char NOCB_METHOD           = 'J';
    static const char MODE_METHOD           = 'L';

    /* remove outliers */
    static const char IQR_METHOD            = 'M';
    static const char PERCENTILE_METHOD     = 'N';
    static const char TUKEY_METHOD          = 'P';
    static const char Z_SCORE_METHOD        = 'Q';
}

#endif //UFCITY_METHODS_H
