// #include <>
// #include <>

#include <string>

using namespace std;


class UserProfile{
    static int user_id;

    public:
        UserProfile(string user_name = "guest", int level = 0) : user_name(user_name), level(level)
        {
            login_count = guess_time = guess_correct_time = 0;
            guess_correct_ratio = 0;

            user_id ++;
            my_id = user_id;
        }

        bool operator==(const UserProfile &rhs){
            return (*this).get_level() - rhs.get_level() < 1e-3;
        }

        bool operator!=(const UserProfile &rhs){
            return !(*this == rhs);
        }

        float get_level() const{
            return guess_time == 0? 0 : guess_correct_time / guess_time;
        }



    private:
        int login_record, login_count, guess_time, guess_correct_time, level;
        int my_id;
        string user_name;
        float guess_correct_ratio;
        
};

int UserProfile::user_id = 0;
