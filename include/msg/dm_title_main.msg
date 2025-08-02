const char STR_800B32A8[] =
    "This game is not designed" MSG_NEWLINE
    "for use on this system." MSG_END;

/**
 * Original name: _mesBootContErr
 */
const char _mesBootContErr[] =
#if VERSION_US
    "There is no controller" MSG_NEWLINE
    "connected. Please turn OFF" MSG_NEWLINE
    "the Nintendo* 64 and insert" MSG_NEWLINE
    "a controller in socket 1."
#elif VERSION_JP
    ""
#endif
    MSG_END;

/**
 * Original name: _mesBootCSumErr
 */
const char _mesBootCSumErr[] =
#if VERSION_US
    "A Backup File is damaged." MSG_NEWLINE
    "Press the A Button to delete this file."
#elif VERSION_JP
    ""
#endif
    MSG_END;
