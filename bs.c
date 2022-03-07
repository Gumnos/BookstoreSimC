#include <stdlib.h>
#include <stdio.h>

#define RENT_DUE_IN_N_DAYS 10
#define ROLLBUFFERSIZE 1000

#define COLOR 1
#ifdef COLOR
#define RED "\033[31m"
#define BRRED "\033[31;1m"
#define WHITE "\033[1m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#else
#define RED ""
#define BRRED ""
#define WHITE ""
#define GREEN ""
#define RESET ""
#endif

int should_report(tries) {
    return !(tries % 1000);
}

enum Event {
    CUSTOMER_NEEDS_TOILET,
    SHOPLIFTER,
    BOOK_DONT_HAVE,
    WILD_ANIMAL,
    COMPLAINT,
    PURCHASES_BOOK,
    RUN_OUT_OF_TEA,
    PRINTER_BROKEN,
    CANT_FIND_BOOK,
    HAGGLING,
    PHONE_RINGS,
    BUY_YOUR_OWN_BOOKS,
    END
    };

const char* const descriptions[] = {
    "customer needs toilet",
    RED "shoplifter" RESET,
    "book don't have",
    "wild animal",
    "complaint",
    GREEN "PURCHASES BOOK" RESET,
    "run out of tea",
    "printer broken",
    "can't find book",
    "haggling",
    "phone rings",
    BRRED "buy your own books" RESET,
    WHITE "NEW DAY" RESET
    };

int main() {
    unsigned long tries=0;
    int time, money, patience, days;
    int keep_trying = 1;
    int max_money = 1;
    int roll;
    int rolls[ROLLBUFFERSIZE];
    unsigned int roll_index;
    while (keep_trying) {
        if (should_report(++tries)) {
            printf(".");
            fflush(stdout);
        }
        days = money = 0;
        roll_index = 0;
        while (++days < RENT_DUE_IN_N_DAYS && (keep_trying = (money < 10))) {
            // a new day
            rolls[roll_index++] = END;
            if (roll_index == ROLLBUFFERSIZE) {
                printf("Too many rolls: %u\n", roll_index);
                exit(1);
            }
            time = patience = 10;
            while (patience > 0 && time > 0 && money < 10) {
                roll = arc4random_uniform(END);
                rolls[roll_index++] = roll;
                if (roll_index == ROLLBUFFERSIZE) {
                    printf("Too many rolls: %u\n", roll_index);
                    exit(1);
                }
                switch (roll) {
                case CUSTOMER_NEEDS_TOILET: --patience; break;
                case SHOPLIFTER: --money; break;
                case BOOK_DONT_HAVE: --time; break;
                case WILD_ANIMAL: --time; break;
                case COMPLAINT: --patience; break;
                case PURCHASES_BOOK: ++money; break;
                case RUN_OUT_OF_TEA: --patience; break;
                case PRINTER_BROKEN: time -= 2; break;
                case CANT_FIND_BOOK: time -= 3; break;
                case HAGGLING: patience -= 3; break;
                case PHONE_RINGS: --time; --patience; break;
                case BUY_YOUR_OWN_BOOKS: money -= 2; break;
                default:
                    printf("What? %i\n", roll);
                    exit(1);
                }
            }
        }
        if (money > max_money) {
            printf("$%i", max_money=money);
            fflush(stdout);
        }
    }
    printf("\n");
    for (int i=0; i< roll_index; i++)
        printf("%s, ", descriptions[rolls[i]]);
    printf("\n");
    printf("After %lu tries, earned $%i with patience=%i & time=%i on day %i\n",
        tries,
        money,
        patience,
        time,
        days-1);
}
