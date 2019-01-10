// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef DODO_TEST_ORLEANS_SERVICE_H
#define DODO_TEST_ORLEANS_SERVICE_H

#include <string_view>
#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>
#include <chrono>

#include <google/protobuf/util/json_util.h>

#include <gayrpc/core/gayrpc_meta.pb.h>
#include "orleans_service.pb.h"

#include <gayrpc/core/GayRpcType.h>
#include <gayrpc/core/GayRpcError.h>
#include <gayrpc/core/GayRpcTypeHandler.h>
#include <gayrpc/core/GayRpcClient.h>
#include <gayrpc/core/GayRpcService.h>
#include <gayrpc/core/GayRpcReply.h>

namespace dodo {
namespace test {

    using namespace gayrpc::core;
    using namespace google::protobuf::util;
    
    enum class orleans_service_ServiceID:uint32_t
    {
        OrleansService,
        
    };

    
    enum class OrleansServiceMsgID:uint64_t
    {
        Request = 2333,
        
    };

    class OrleansServiceClient : public BaseClient
    {
    public:
        using PTR = std::shared_ptr<OrleansServiceClient>;
        using WeakPtr = std::weak_ptr<OrleansServiceClient>;

        using RequestHandle = std::function<void(const dodo::test::OrleansResponse&, const gayrpc::core::RpcError&)>;
        

    public:
        void Request(const dodo::test::OrleansRequest& request,
            const RequestHandle& handle = nullptr)
        {
            call<dodo::test::OrleansResponse>(request, 
                static_cast<uint32_t>(orleans_service_ServiceID::OrleansService), 
                static_cast<uint64_t>(OrleansServiceMsgID::Request), 
                handle);
        }
        
        void Request(const dodo::test::OrleansRequest& request,
            const RequestHandle& handle,
            std::chrono::seconds timeout, 
            BaseClient::TIMEOUT_CALLBACK timeoutCallback)
        {
            call<dodo::test::OrleansResponse>(request, 
                static_cast<uint32_t>(orleans_service_ServiceID::OrleansService), 
                static_cast<uint64_t>(OrleansServiceMsgID::Request), 
                handle,
                timeout,
                std::move(timeoutCallback));
        }
        

        dodo::test::OrleansResponse SyncRequest(
            const dodo::test::OrleansRequest& request,
            gayrpc::core::RpcError& error)
        {
            auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
            auto responsePromise = std::make_shared<std::promise<dodo::test::OrleansResponse>>();

            Request(request, [responsePromise, errorPromise](const dodo::test::OrleansResponse& response,
                const gayrpc::core::RpcError& error) {
                errorPromise->set_value(error);
                responsePromise->set_value(response);
            });

            error = errorPromise->get_future().get();
            return responsePromise->get_future().get();
        }
        

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            struct make_shared_enabler : public OrleansServiceClient
            {
            public:
                make_shared_enabler(const RpcTypeHandleManager::PTR& rpcHandlerManager,
                    const UnaryServerInterceptor& inboundInterceptor,
                    const UnaryServerInterceptor& outboundInterceptor)
                    : 
                    OrleansServiceClient(rpcHandlerManager, inboundInterceptor, outboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(rpcHandlerManager, inboundInterceptor, outboundInterceptor));
            client->installResponseStub(rpcHandlerManager, static_cast<uint32_t>(orleans_service_ServiceID::OrleansService));

            return client;
        }

    private:
        using BaseClient::BaseClient;
    };

    class OrleansServiceService : public BaseService
    {
    public:
        using PTR = std::shared_ptr<OrleansServiceService>;
        using WeakPtr = std::weak_ptr<OrleansServiceService>;

        using RequestReply = TemplateReply<dodo::test::OrleansResponse>;
        

        using BaseService::BaseService;

        virtual ~OrleansServiceService()
        {
        }

        virtual void onClose() {}

        static inline bool Install(const OrleansServiceService::PTR& service);
    private:
        virtual void Request(const dodo::test::OrleansRequest& request, 
            const dodo::test::OrleansServiceService::RequestReply::PTR& replyObj,
            InterceptorContextType context) = 0;
        

    private:

        static void Request_stub(const RpcMeta& meta,
            const std::string_view& data,
            const OrleansServiceService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor,
            InterceptorContextType context)
        {
            dodo::test::OrleansRequest request;
            parseRequestWrapper(request, meta, data, inboundInterceptor, [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message, InterceptorContextType context) {
                auto replyObject = std::make_shared<RequestReply>(meta, outboundInterceptor);
                service->Request(request, replyObject, std::move(context));
            }, context);
        }
        
    };

    inline bool OrleansServiceService::Install(const OrleansServiceService::PTR& service)
    {
        auto rpcTypeHandleManager = service->getServiceContext().getTypeHandleManager();
        auto inboundInterceptor = service->getServiceContext().getInInterceptor();
        auto outboundInterceptor = service->getServiceContext().getOutInterceptor();

        using OrleansServiceServiceRequestHandler = std::function<void(const RpcMeta&,
            const std::string_view& data,
            const OrleansServiceService::PTR&,
            const UnaryServerInterceptor&,
            const UnaryServerInterceptor&,
            InterceptorContextType)>;

        using OrleansServiceServiceHandlerMapById = std::unordered_map<uint64_t, OrleansServiceServiceRequestHandler>;
        using OrleansServiceServiceHandlerMapByStr = std::unordered_map<std::string, OrleansServiceServiceRequestHandler>;

        // TODO::static unordered map
        auto serviceHandlerMapById = std::make_shared<OrleansServiceServiceHandlerMapById>();
        auto serviceHandlerMapByStr = std::make_shared<OrleansServiceServiceHandlerMapByStr>();

        const std::string namespaceStr = "dodo.test.";

        (*serviceHandlerMapById)[static_cast<uint64_t>(OrleansServiceMsgID::Request)] = OrleansServiceService::Request_stub;
        
        (*serviceHandlerMapByStr)[namespaceStr+"OrleansService.Request"] = OrleansServiceService::Request_stub;
        

        auto requestStub = [service,
            serviceHandlerMapById,
            serviceHandlerMapByStr,
            inboundInterceptor,
            outboundInterceptor](const RpcMeta& meta, const std::string_view& data, InterceptorContextType context) {
            
            if (meta.type() != RpcMeta::REQUEST)
            {
                throw std::runtime_error("meta type not request, It is:" + std::to_string(meta.type()));
            }
            
            OrleansServiceServiceRequestHandler handler;

            if (!meta.request_info().strmethod().empty())
            {
                auto it = serviceHandlerMapByStr->find(meta.request_info().strmethod());
                if (it == serviceHandlerMapByStr->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().strmethod());
                }
                handler = (*it).second;
            }
            else
            {
                auto it = serviceHandlerMapById->find(meta.request_info().intmethod());
                if (it == serviceHandlerMapById->end())
                {
                    throw std::runtime_error("not found handle, method:" + meta.request_info().intmethod());
                }
                handler = (*it).second;
            }

            handler(meta,
                data,
                service,
                inboundInterceptor,
                outboundInterceptor,
                context);
        };

        return rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub, static_cast<uint32_t>(orleans_service_ServiceID::OrleansService));
    }
    
}
}

#endif

