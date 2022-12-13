#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int ADMIN_ROLE = 0;
const int USER_ROLE = 1;

struct user {
  char login[10];
  char password[10];
  //int numberBoughtTickets;
  //char boughtTickets;
  int role;  //0 - Admin, 1 - User
};

struct Trains {
  int numberOfTrain;  //номер поезда
  char arrivalCity;  //пункт назначения
  int departureDay;  //дату отправления
  int departureMonth;
  int departureYear;
  int departureHour;  //время отправления
  int departureMinute;
  int departureSecond;
  int arrivalDay;  //время прибытия на конечный пункт
  int arrivalMonth;
  int arrivalYear;
  int arrivalHour;
  int arrivalMinute;
  int arrivalSecond;
  double ticketPrice;  //стоимость одного билета
  int quantityOfRemainingTickets;  //количество оставшихся для продажи билетов
  int quantityOfSoldTickets;  //количество проданных билетов
};

struct IndividualWork {
  char x;
  int day;
  int month;
  int year;
  int hourToStart;
  int minuteToStart;
  int secondToString;
  int hourToEnd;
  int minuteToEnd;
  int secondToEnd;
};

struct user users[100];
int users_num = 0;
 

struct train trains[100];
int trains_num = 0;

 
int findUser(char login[10]) {
	for (int i = 0; i < users_num; i++){
	    if (strcmp(users[i].login, login) == 0) {
	      return i;
		}
	}
  return -1;
}

void doUserList(void) {
	while (1) {
	    system("cls");  //clear screen console
	    fflush(stdin);  //clear input
	    for (int i = 0; i < user_num; i++) {
	    	printf("%d. %s / %s (%s)\n", i + 1, users[i].login, users[i].password,
		    		users[i].role == ADMIN_ROLE ? "admin" : "user");
		}
		printf("Enter 0 to return:");
		int i;
		scanf("%d", &i);
		if (i == 0) {
			return;
		}
	}
}

void doAddUser() {
	system("cls");
	fflush(stdin);  //clear input
	  
	struct user u;
	printf("Enter login: ");
	scanf("%s", u.login);
	printf("Enter password: ");
	scanf("%s", u.password);
	printf("Enter role (0 - Admin, 1 - User): ");
	scanf("%d", &u.role);
	if (u.role != 0) {
		u.role = 1;
	}
	users[users_num++] = u;
	
	showMessage("User added");
}


//1.реализовать авторизацию для
//входа в систему, функционал администратора и функционал
//пользователя. 

//2.Разработка программы продажи железнодорожных билетов.
//Железнодорожный вокзал осуществляет продажу 
//билетов на поезда дальнего
//следования. Для каждого поезда указаны: номер поезда, 
//пункт назначения,
//дату отправления, время отправления,
//время прибытия на конечный пункт,
//стоимость одного билета, количество оставшихся 
//для продажи билетов,
//количество проданных билетов. 

//3.Индивидуальное задание: обеспечить функциональную 
//возможность
//покупки билетов на конкретный рейс в требуемом 
//количестве (при этом
//количество оставшихся для продажи билетов 
//и количество проданных
//билетов обновляется). Вывести номер, время отправления 
//и наличие билетов
//для поездов, прибывающих в город Х в интервале 
//от А до B (X, A, B
//вводятся с клавиатуры). 
