#ifndef BLOCKERS_WORKER_H_
#define BLOCKERS_WORKER_H_

#include <string>
#include <vector>
#include <map>
#include <mutex>

class CTPParser;
class ABPFilterParser;
class GURL;
struct sqlite3;

namespace net {
namespace blockers {

class BlockersWorker {
public:
    BlockersWorker();
    ~BlockersWorker();

    bool shouldTPBlockUrl(const std::string& base_host, const std::string& host);
    bool shouldAdBlockUrl(const std::string& base_host, const std::string& url, unsigned int resource_type);
    std::string getHTTPSURL(const GURL* url);

private:
    bool InitTP();
    bool InitAdBlock();
    bool InitHTTPSE();
    std::string getHTTPSNewHostFromIds(const std::string& ruleIds, const std::string& originalUrl);
    std::string applyHTTPSRule(const std::string& originalUrl, const std::string& rule);
    std::vector<std::string> getTPThirdPartyHosts(const std::string& base_host);

    bool GetData(const char* fileName, std::vector<unsigned char>& buffer, bool only_file_name = false);

    std::string correcttoRuleToRE2Engine(const std::string& to);

    std::vector<unsigned char> tp_buffer_;
    std::vector<unsigned char> adblock_buffer_;
    sqlite3* httpse_db_;
    CTPParser* tp_parser_;
    ABPFilterParser* adblock_parser_;

    std::map<std::string, std::vector<std::string>> tp_third_party_hosts_;
    std::vector<std::string> tp_third_party_base_hosts_;
    // That is just temporarily, we will have to figure that out
    // inside the tracking protection lib
    std::vector<std::string> tp_white_list_;

    std::mutex httpse_init_mutex_;
    std::mutex adblock_init_mutex_;
    std::mutex tp_init_mutex_;
    std::mutex tp_get_third_party_hosts_mutex_;
};

}  // namespace blockers
}  // namespace net

#endif