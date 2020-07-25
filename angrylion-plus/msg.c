#define MSG_BUFFER_LEN 4096

void msg_error(const char * err, ...)
{
    va_list arg;
    va_start(arg, err);
    char buf[MSG_BUFFER_LEN];
    vsnprintf(buf, sizeof(buf), err, arg);
    print("[al+ error] ", buf);
    va_end(arg);
    exit(0);
}

void msg_warning(const char* err, ...)
{
    va_list arg;
    va_start(arg, err);
    char buf[MSG_BUFFER_LEN];
    vsnprintf(buf, sizeof(buf), err, arg);
    print("[al+ warning] ", buf);
    va_end(arg);
}

void msg_debug(const char* err, ...)
{
    va_list arg;
    va_start(arg, err);
    char buf[MSG_BUFFER_LEN];
    vsnprintf(buf, sizeof(buf), err, arg);
    strncat(buf, "\n", sizeof(buf));
    print("[al+ debug] ", buf);
    va_end(arg);
}
