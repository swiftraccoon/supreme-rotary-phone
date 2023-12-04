class CustomFormatter : public spdlog::formatter
{
public:
    void format(const spdlog::details::log_msg &msg, spdlog::memory_buf_t &dest) override
    {
        fmt::format_to(dest, "[{}] {} {} {}",
                       fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(msg.time)),
                       msg.source.filename,
                       msg.source.funcname,
                       msg.payload);
    }
};
