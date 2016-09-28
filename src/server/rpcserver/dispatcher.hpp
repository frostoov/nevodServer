#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <functional>
#include <utility>
#include <vector>

#include "fault.hpp"
#include "request.hpp"
#include "response.hpp"
#include "value.hpp"

class MethodWrapper {
public:
    using Method = std::function<Value(const Request::Parameters&)>;

    explicit MethodWrapper(Method method) : method_(method) {}

    MethodWrapper(const MethodWrapper&) = delete;
    MethodWrapper& operator=(const MethodWrapper&) = delete;

    bool isHidden() const { return isHidden_; }
    void setHidden(bool hidden = true) { isHidden_ = hidden; }

    MethodWrapper& setHelpText(std::string help);
    const std::string& getHelpText() const { return helpText_; }

    template <typename... ParameterTypes>
    MethodWrapper& addSignature(Value::Type returnType,
                                ParameterTypes... parameterTypes) {
        signatures_.emplace_back(
            std::initializer_list<Value::Type>{returnType, parameterTypes...});
        return *this;
    }

    const std::vector<std::vector<Value::Type>>& getSignatures() const {
        return signatures_;
    }

    Value operator()(const Request::Parameters& params) const {
        return method_(params);
    }

private:
    Method method_;
    bool isHidden_ = false;
    std::string helpText_;
    std::vector<std::vector<Value::Type>> signatures_;
};

template <typename>
struct ToStdFunction;

template <typename ReturnType, typename... ParameterTypes>
struct ToStdFunction<ReturnType (*)(ParameterTypes...)> {
    typedef std::function<ReturnType(ParameterTypes...)> Type;
};

template <typename ReturnType, typename T, typename... ParameterTypes>
struct ToStdFunction<ReturnType (T::*)(ParameterTypes...)> {
    typedef std::function<ReturnType(ParameterTypes...)> Type;
};

template <typename ReturnType, typename T, typename... ParameterTypes>
struct ToStdFunction<ReturnType (T::*)(ParameterTypes...) const> {
    typedef std::function<ReturnType(ParameterTypes...)> Type;
};

template <typename MethodType, bool isClass>
struct StdFunction {};

template <typename MethodType>
struct StdFunction<MethodType, false> {
    typedef typename ToStdFunction<MethodType>::Type Type;
};

template <typename MethodType>
struct StdFunction<MethodType, true> {
    typedef
        typename ToStdFunction<decltype(&MethodType::operator())>::Type Type;
};

class Dispatcher {
public:
    std::vector<std::string> getMethodNames(bool includeHidden = false) const;
    MethodWrapper& getMethod(const std::string& name);

    MethodWrapper& addMethod(std::string name, MethodWrapper::Method method);

    template <typename MethodType>
    typename std::enable_if<
        !std::is_convertible<MethodType, MethodWrapper::Method>::value &&
            !std::is_member_pointer<MethodType>::value,
        MethodWrapper>::type&
    addMethod(std::string name, MethodType method) {
        static_assert(!std::is_bind_expression<MethodType>::value,
                      "Use AddMethod with 3 arguments to add member method");
        typename StdFunction<MethodType, std::is_class<MethodType>::value>::Type
            function(std::move(method));
        return addMethodInternal(std::move(name), std::move(function));
    }

    template <typename T>
    MethodWrapper& addMethod(std::string name,
                             Value (T::*method)(const Request::Parameters&),
                             T& instance) {
        return addMethod(std::move(name),
                         std::bind(method, &instance, std::placeholders::_1));
    }

    template <typename T>
    MethodWrapper& addMethod(std::string name,
                             Value (T::*method)(const Request::Parameters&)
                                 const,
                             T& instance) {
        return addMethod(std::move(name),
                         std::bind(method, &instance, std::placeholders::_1));
    }

    template <typename ReturnType, typename T, typename... ParameterTypes>
    MethodWrapper& addMethod(std::string name,
                             ReturnType (T::*method)(ParameterTypes...),
                             T& instance) {
        std::function<ReturnType(ParameterTypes...)> function =
            [&instance, method](ParameterTypes&&... params) -> ReturnType {
            return (instance.*method)(std::forward<ParameterTypes>(params)...);
        };
        return addMethodInternal(std::move(name), std::move(function));
    }

    template <typename ReturnType, typename T, typename... ParameterTypes>
    MethodWrapper& addMethod(std::string name,
                             ReturnType (T::*method)(ParameterTypes...) const,
                             T& instance) {
        std::function<ReturnType(ParameterTypes...)> function =
            [&instance, method](ParameterTypes&&... params) -> ReturnType {
            return (instance.*method)(std::forward<ParameterTypes>(params)...);
        };
        return addMethodInternal(std::move(name), std::move(function));
    }

    void RemoveMethod(const std::string& name);

    Response Invoke(const std::string& name,
                    const Request::Parameters& parameters,
                    const Value& id) const;

private:
    template <typename ReturnType, typename... ParameterTypes>
    MethodWrapper& addMethodInternal(
        std::string name,
        std::function<ReturnType(ParameterTypes...)> method) {
        return addMethodInternal(std::move(name), std::move(method),
                                 std::index_sequence_for<ParameterTypes...>{});
    }

    template <typename... ParameterTypes>
    MethodWrapper& addMethodInternal(
        std::string name,
        std::function<void(ParameterTypes...)> method) {
        std::function<Value(ParameterTypes...)> returnMethod =
            [method](ParameterTypes&&... params) -> Value {
            method(std::forward<ParameterTypes>(params)...);
            return Value();
        };
        return addMethodInternal(std::move(name), std::move(returnMethod),
                                 std::index_sequence_for<ParameterTypes...>{});
    }

    template <typename ReturnType,
              typename... ParameterTypes,
              std::size_t... index>
    MethodWrapper& addMethodInternal(
        std::string name,
        std::function<ReturnType(ParameterTypes...)> method,
        std::index_sequence<index...>) {
        MethodWrapper::Method realMethod =
            [method](const Request::Parameters& params) -> Value {
            if (params.size() != sizeof...(ParameterTypes)) {
                throw InvalidParametersFault();
            }
            return method(
                params[index]
                    .asType<typename std::decay<ParameterTypes>::type>()...);
        };
        return addMethod(std::move(name), std::move(realMethod));
    }

    std::map<std::string, MethodWrapper> methods_;
};

#endif//DISPATCHER_HPP
