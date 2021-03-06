// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: uquantapi.proto
// Original file comments:
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_uquantapi_2eproto__INCLUDED
#define GRPC_uquantapi_2eproto__INCLUDED

#include "uquantapi.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace uquantapi {

// The greeting service definition.
class Greeter final {
 public:
  static constexpr char const* service_full_name() {
    return "uquantapi.Greeter";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Sends a greeting
    virtual ::grpc::Status SayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::uquantapi::HelloReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>> AsyncSayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>>(AsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>> PrepareAsyncSayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>>(PrepareAsyncSayHelloRaw(context, request, cq));
    }
    virtual ::grpc::Status SayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::uquantapi::HelloReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>> AsyncSayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>>(AsyncSayHelloAgainRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>> PrepareAsyncSayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>>(PrepareAsyncSayHelloAgainRaw(context, request, cq));
    }
    virtual ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>* AsyncSayHelloRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>* PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>* AsyncSayHelloAgainRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::HelloReply>* PrepareAsyncSayHelloAgainRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status SayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::uquantapi::HelloReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>> AsyncSayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>>(AsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>> PrepareAsyncSayHello(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>>(PrepareAsyncSayHelloRaw(context, request, cq));
    }
    ::grpc::Status SayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::uquantapi::HelloReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>> AsyncSayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>>(AsyncSayHelloAgainRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>> PrepareAsyncSayHelloAgain(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>>(PrepareAsyncSayHelloAgainRaw(context, request, cq));
    }
    ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>* AsyncSayHelloRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>* PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>* AsyncSayHelloAgainRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::HelloReply>* PrepareAsyncSayHelloAgainRaw(::grpc::ClientContext* context, const ::uquantapi::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SayHello_;
    const ::grpc::internal::RpcMethod rpcmethod_SayHelloAgain_;
    const ::grpc::internal::RpcMethod rpcmethod_getFutureBars_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Sends a greeting
    virtual ::grpc::Status SayHello(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response);
    virtual ::grpc::Status SayHelloAgain(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response);
    virtual ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_SayHello() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHello(::grpc::ServerContext* context, ::uquantapi::HelloRequest* request, ::grpc::ServerAsyncResponseWriter< ::uquantapi::HelloReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SayHelloAgain : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_SayHelloAgain() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SayHelloAgain() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloAgain(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHelloAgain(::grpc::ServerContext* context, ::uquantapi::HelloRequest* request, ::grpc::ServerAsyncResponseWriter< ::uquantapi::HelloReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_getFutureBars() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestgetFutureBars(::grpc::ServerContext* context, ::uquantapi::kBarRequest* request, ::grpc::ServerAsyncResponseWriter< ::uquantapi::kBarReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SayHello<WithAsyncMethod_SayHelloAgain<WithAsyncMethod_getFutureBars<Service > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_SayHello() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SayHelloAgain : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_SayHelloAgain() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SayHelloAgain() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloAgain(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_getFutureBars() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_SayHello() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::uquantapi::HelloRequest, ::uquantapi::HelloReply>(std::bind(&WithStreamedUnaryMethod_SayHello<BaseClass>::StreamedSayHello, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSayHello(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::uquantapi::HelloRequest,::uquantapi::HelloReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SayHelloAgain : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_SayHelloAgain() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::uquantapi::HelloRequest, ::uquantapi::HelloReply>(std::bind(&WithStreamedUnaryMethod_SayHelloAgain<BaseClass>::StreamedSayHelloAgain, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_SayHelloAgain() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SayHelloAgain(::grpc::ServerContext* context, const ::uquantapi::HelloRequest* request, ::uquantapi::HelloReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSayHelloAgain(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::uquantapi::HelloRequest,::uquantapi::HelloReply>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_getFutureBars() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler< ::uquantapi::kBarRequest, ::uquantapi::kBarReply>(std::bind(&WithStreamedUnaryMethod_getFutureBars<BaseClass>::StreamedgetFutureBars, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedgetFutureBars(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::uquantapi::kBarRequest,::uquantapi::kBarReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SayHello<WithStreamedUnaryMethod_SayHelloAgain<WithStreamedUnaryMethod_getFutureBars<Service > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SayHello<WithStreamedUnaryMethod_SayHelloAgain<WithStreamedUnaryMethod_getFutureBars<Service > > > StreamedService;
};
// class

class FutureApi final {
 public:
  static constexpr char const* service_full_name() {
    return "uquantapi.FutureApi";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_getFutureBars_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_getFutureBars() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestgetFutureBars(::grpc::ServerContext* context, ::uquantapi::kBarRequest* request, ::grpc::ServerAsyncResponseWriter< ::uquantapi::kBarReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_getFutureBars<Service > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_getFutureBars() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_getFutureBars() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::uquantapi::kBarRequest, ::uquantapi::kBarReply>(std::bind(&WithStreamedUnaryMethod_getFutureBars<BaseClass>::StreamedgetFutureBars, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedgetFutureBars(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::uquantapi::kBarRequest,::uquantapi::kBarReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_getFutureBars<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_getFutureBars<Service > StreamedService;
};

class StockApi final {
 public:
  static constexpr char const* service_full_name() {
    return "uquantapi.StockApi";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status getFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::uquantapi::kBarReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> AsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(AsyncgetFutureBarsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>> PrepareAsyncgetFutureBars(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>>(PrepareAsyncgetFutureBarsRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* AsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::uquantapi::kBarReply>* PrepareAsyncgetFutureBarsRaw(::grpc::ClientContext* context, const ::uquantapi::kBarRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_getFutureBars_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_getFutureBars() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestgetFutureBars(::grpc::ServerContext* context, ::uquantapi::kBarRequest* request, ::grpc::ServerAsyncResponseWriter< ::uquantapi::kBarReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_getFutureBars<Service > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_getFutureBars() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_getFutureBars : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_getFutureBars() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::uquantapi::kBarRequest, ::uquantapi::kBarReply>(std::bind(&WithStreamedUnaryMethod_getFutureBars<BaseClass>::StreamedgetFutureBars, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_getFutureBars() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status getFutureBars(::grpc::ServerContext* context, const ::uquantapi::kBarRequest* request, ::uquantapi::kBarReply* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedgetFutureBars(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::uquantapi::kBarRequest,::uquantapi::kBarReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_getFutureBars<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_getFutureBars<Service > StreamedService;
};

}  // namespace uquantapi


#endif  // GRPC_uquantapi_2eproto__INCLUDED
