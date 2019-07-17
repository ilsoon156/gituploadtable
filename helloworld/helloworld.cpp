#include <eosiolib/eosio.hpp>

using namespace eosio;

 CONTRACT helloworld: public contract {
    public:
        using contract::contract;

        ACTION hi (name user){
            check(has_auth(get_self() ) || has_auth("ispfirst1234"_n)), "Who are you?");
            //bool isTrue = has_auth(getself()) || has_auth("powerintel12"_n);
            /*check(has_auth(get_self() ), "Who are you?");
            require_auth("ispfirst1234"_n);
            require_auth(get_self() );

            require_auth(user);

            has_auth() -> true/false 반환*/

            print("hello, ", user);
        }

    private:

 };