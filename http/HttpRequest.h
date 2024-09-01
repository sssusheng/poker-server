#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "HttpResponse.h"
#include "Buffer.h"
#include <map>
#include <functional>


// 当前的解析状态
enum struct PrecessState:char {
    ParseReqLine,
    ParseReqHeaders,
    ParseReqBody,
    ParseReqDone
};

// 定义http请求结构体
class HttpRequest {
public:
    HttpRequest();

    ~HttpRequest();

    // 重置
    void reset();

    // 添加请求头
    void addHeader(std::string key, std::string value);

    // 根据key得到请求头的value
    std::string getHeader(std::string key);

    // 解析请求行
    bool parseRequestLine(Buffer *readBuf);

    // 解析请求头
    bool parseRequestHeader(Buffer *readBuf);

    // 解析http请求协议
    bool parseHttpRequest(Buffer *readBuf, HttpResponse *response, Buffer *sendBuf, int socket);

    // 处理http请求协议
    bool processHttpRequest(HttpResponse *response);

    // 解码字符串
    std::string decodeMsg(std::string from);

    const std::string getFileType(std::string name);

    static void sendDir(std::string dirName, Buffer *sendBuf, int cfd);

    static void sendFile(std::string dirName, Buffer *sendBuf, int cfd);

    inline void setMethod(std::string method) {
        m_method = method;
    }

    inline void seturl(std::string url) {
        m_url = url;
    }

    inline void setVersion(std::string version) {
        m_version = version;
    }

    // 获取处理状态
    inline PrecessState getState() {
        return m_curState;
    }

    inline void setState(PrecessState state) {
        m_curState = state;
    }

private:
    char *splitRequestLine(const char *start, const char *end,
                           const char *sub, std::function<void(std::string)> callback);

    int hexToDec(char c);

private:
    std::string m_method;
    std::string m_url;
    std::string m_version;
    std::map<std::string, std::string> m_reqHeaders;
    PrecessState m_curState;
};


#endif //HTTPREQUEST_H
