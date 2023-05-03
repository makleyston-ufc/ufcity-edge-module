//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_METHODS_H
#define UFCITY_METHODS_H

namespace methods{

    static const char NONE                  = 'A';

    /* fata grouping */
    static const char FIXED_SIZE_GROUPING            = 'B';
    static const char HAPPENS_FIRST_GROUPING         = 'C';
    static const char AT_LEAST_TIME_GROUPING         = 'D';
    static const char AT_LEAST_TIME_AND_SIZE_GROUPING= 'I';

    /* missing data */
    static const char MEAN_MISSING_DATA_METHOD           = 'E';
    static const char MEDIAN_MISSING_DATA_METHOD         = 'F';
    static const char LOCF_MISSING_DATA_METHOD           = 'G'; /* Last Observation Carried Forward  */
    static const char INTERPOLATION_MISSING_DATA_METHOD  = 'H';
    static const char NOCB_MISSING_DATA_METHOD           = 'J';
    static const char MODE_MISSING_DATA_METHOD           = 'L';

    /* remove outliers */
    static const char IQR_REMOVE_OUTLIERS_METHOD            = 'M';
    static const char PERCENTILE_REMOVE_OUTLIERS_METHOD     = 'N';
    static const char TUKEY_REMOVE_OUTLIERS_METHOD          = 'P';
    static const char Z_SCORE_REMOVE_OUTLIERS_METHOD        = 'Q';

    /* data aggregation */
    static const char MEAN_AGGREGATION_METHOD           = 'R';
    static const char MEDIAN_AGGREGATION_METHOD         = 'S';
    static const char MAX_AGGREGATION_METHOD            = 'T';
    static const char MIN_AGGREGATION_METHOD            = 'U';
}

#endif //UFCITY_METHODS_H
