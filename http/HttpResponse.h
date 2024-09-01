#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "Buffer.h"
#include <map>
#include <functional>


// 定义状态码枚举
enum struct StatusCode {
    Unknown,
    OK = 200,
    MovedPermanently = 301,
    MovedTemporarily = 302,
    BadRequest = 400,
    NotFound = 404
};

// 定义结构体
class HttpResponse {
public:
    HttpResponse();

    ~HttpResponse();

    std::function<void(const std::string, Buffer *, int)> sendDataFunc;

    // 添加响应头
    void addHeader(const std::string key, const std::string value);

    // 组织http响应数据
    void prepareMsg(Buffer *sendBuf, int socket);

    inline void setFileName(std::string name) {
        m_fileName = name;
    }

    inline void setStatusCode(StatusCode code) {
        m_statusCode = code;
    }

private:
    // 状态行: 状态码, 状态描述
    StatusCode m_statusCode;
    std::string m_fileName;
    // 响应头 - 键值对
    std::map<std::string, std::string> m_headers;
    // 定义状态码和描述的对应关系
    const std::map<int, std::string> m_info = {
        {200, "OK"},
        {301, "MovedPermanently"},
        {302, "MovedTemporarily"},
        {400, "BadRequest"},
        {404, "NotFound"},
    };
};


#endif //HTTPRESPONSE_H
