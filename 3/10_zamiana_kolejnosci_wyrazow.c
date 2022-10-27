#include <stdio.h>

void reverse(char text[]) {

    int size = 0;
    for (size = 0; text[size]; size++);

    char words[100][100];

    int current_word = 0;

    for (int i = 0, j = 0; i < size; i++, j++) {
        if (text[i] == ' ') {
            j = 0;
            current_word++;
        }
        words[current_word][j] += text[i];
    }

    for (int i = current_word - 1; i >= 0; i--) {
        printf("%s ", words[i]);
    }

}

int main() {
    char letters[] = "wyraz1 wyraz2 wyraz3 wyraz1231 wyrazabc";
    reverse(letters);
//    printf("%s", letters);
}

//
//#include <stdio.h>
//
//void reverse(char text[]) {
//
//    int size = 0;
//    for (size = 0; text[size]; size++);
//
//    char words[100][100];
//
//    int current_word = 0;
//
//    for (int i = 0, j = 0; i < size; i++, j++) {
//        if (text[i] == ' ') {
//            j = 0;
//            current_word++;
//        } else {
//            words[current_word][j] += text[i];
//        }
//    }
//
//    for (int i = current_word - 1; i >= 0; i--) {
//        printf("%s", words[i]);
//    }
//
//}
//
//int main() {
//    char letters[] = "wyraz1 wyraz2 wyraz3 wyraz1231 wyrazabc";
//    reverse(letters);
////    printf("%s", letters);
//}

