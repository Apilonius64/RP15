#if !defined(COMMON_H_RP15_23)
#define COMMON_H_RP15_23

#include <vector>
#include <stddef.h>
#include <memory>

namespace r15
{
    typedef void VOID;
    typedef char CHAR;
    typedef CHAR BYTE;
    typedef const char CSTR;
    typedef VOID* P_VOID;
    typedef size_t VARSIZE;
    typedef bool BOOL;

    template <typename T>
    using PShared = std::shared_ptr<T>;
    template <typename T>
    using PUnique = std::unique_ptr<T>;
    template <typename T>
    using PWeak = std::weak_ptr<T>;

    constexpr BOOL False = false;
    constexpr BOOL True = true;

    template <typename T>
    class Operators {
    private:
        T value;

    public:
        Operators(T _value) {
            value = _value;
        }

        T operator|() override {
            
        }
    };

    template <typename For>
    class Handler {
    public:
        typedef enum {
            HR_HANDELED,
            HR_NEXT,
            HR_ERR
        } HandleResult;

        virtual HandleResult handle(For what) = 0;
    };

    template <typename T>
    class Tree {
    private:
        std::vector<PShared<T>> childs;

    public:
        virtual VARSIZE regChild(PShared<T> child);
        virtual PWeak<T> getChild(VARSIZE id) const;

        PShared<T>* Begin() const {
            return childs.begin();
        }

        PShared<T>* End() const {
            return childs.end();
        }

        // Make maybe more specific
        template <
            typename Ret,
            typename Method,
            typename ROperator,
            typename... Args
        >
        Ret stackChildCall(Method m, Ret Initial = 0, ROperator op = Ret::operator+, Args... args) {
            Ret Result;

            for (typename std::vector<PShared<T>*>::iterator It = Begin(); It != End(); ++It) {
                Result.*op((*It)->*m(args...));
            }

            return Result;
        }
    };

    template <typename For>
    class SpecificHandler : public Handler<For> {
    public:
        virtual BOOL canHandle(For what) = 0;
    };

    // Later maybe Tree<T>, etc.
    template <typename For>
    class TreeHandler : public SpecificHandler<For>, Tree<SpecificHandler<For>> {
    public:
        using HandleResult = typename SpecificHandler<For>::HandleResult;

        virtual BOOL canHandle(For what) override;
        virtual HandleResult handle(For what) override;

        virtual void selfCanHandle() = 0;
        virtual void selfHandle() = 0;
    };
} // namespace r15



#endif // COMMON_H_RP15_23
