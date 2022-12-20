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

struct train {
  int numberOfTrain;  //номер поезда
  char destination;  //пункт назначения
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

struct user users[100];  //присвоение значений элементам структуры в 
//процессе объявления переменной, относящейся к типу структуры;
//struct ИмяСтруктуры ИмяПеременной
int users_num = 0;  //промто переменная
 

struct train trains[100];
int trains_num = 0;

//void showMessage(char *msg) {
//    int i;
//    while (1) {
//        system("cls");
//        printf("%s\n", msg);
//        printf("Enter 0 to return:");
//        scanf("%d", &i);
//        if (i == 0) {
//            return;
//        }
//    }
//}
 
int load(void) {
  FILE *file = fopen("test.txt", "rb");
  if (file) {
    fread(&users_num, sizeof(int), 1, file);  //sizeof(int) просто 
//подразумевает значение размера целого числа. 
//(Будь то 32-битная или 64-битная машина, sizeof(int) 
//всегда будет возвращать значение 4 как размер целого числа).
    fread(&trains_num, sizeof(int), 1, file);
    if (users_num > 100 || trains_num > 100) {
            //todo: check file size == sizeof(int) * 2 + users_num * sizeof(struct user) + students_num * sizeof(struct student)
      printf("Invalid file format");
      exit(0);
    }
    if (users_num > 0) {
      fread(users, sizeof(struct user), users_num, file);
//Оператор sizeof предоставляет объем хранения (в байтах)
    }
    if (trains_num > 0) {
      fread(trains, sizeof(struct train), trains_num, file);
    }
    fclose(file);
    return 1;
  }
  return 0;
}

void save(void) {
  FILE *file = fopen("test.txt", "wb");
  fwrite(&users_num, sizeof(int), 1, file);
  fwrite(&trains_num, sizeof(int), 1, file);
  if (users_num > 0) {
    fwrite(users, sizeof(struct user), users_num, file);
  }
  if (trains_num > 0) {
    fwrite(trains, sizeof(struct train), trains_num, file);
  }
  fclose(file);
}

int findUser(char login[10]) {
  for (int i = 0; i < users_num; i++){
    if (strcmp(users[i].login, login) == 0) {
//Для обращения к элементам структуры используется операция "точка":
//имя_переменной_структуры.имя_элемента
//присвоение элементу значения
      return i;
    }
  }
  return -1;
}


void doUserList(void) {
  while (1) {
    system("cls");  //clear screen console
	    //fflush(stdin);  //clear input
    for (int i = 0; i < users_num; i++) {
// %s — строковый формат
      printf("%d. %s / %s (%s)\n", i + 1, users[i].login, users[i].password,
        users[i].role == ADMIN_ROLE ? "admin" : "user");
    }
    printf("Enter 0 to return: ");
    int i;
    scanf("%d", &i);
    if (i == 0) {
      return;
    }
  }
}

void doAddUser(void) {
  system("cls");
	//fflush(stdin);  //clear input	  
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
	//showMessage("User added");
  printf("User added");
}

void doDeleteUser(void) {
  system("cls");
  char login[100];
  printf("Enter login to remove: ");
  scanf("%s", login);
  int index = findUser(login);
  if (index < 0) {
    return;
  }
  printf("Are you sure you want to delete this user? (1 - Yes, 0 - No): ");
  int i;
  scanf("%d", &i);
  if (i != 0) {
  	for (int i = index; i < users_num - 1; i++) {
  	  users[i] = users[i + 1];
	}
	users_num--;
	//showMessage("User removed");
	printf("User deleted");
  }
}

void doUsers(void) {
  while (1) {
  	system("cls");
  	printf("0. Return\n");
  	printf("1. List users\n");
  	printf("2. Add users\n");
  	printf("3. Delete user\n");
  	int i;
  	printf("Select number: ");
  	scanf("%d", &i);
  	switch (i) {
  	  case 0:
  	  	return;
  	  case 1:
  	  	doUserList();
  	  	break;
  	  case 2:
  	  	doAddUser();
  	  	break;
  	  case 3:
  	  	doDeleteUser();
  	  	break;
	}
  }
}

void doListTrains(void) {
  while (1) {
    system("cls");
    printf("+--+-------------+---------------+-----------------+-----------------------------+--------------------+"
	  "-------------------------------+-----------------------+\n");
    printf("| N|  Destination|  Departure date|  Departure time|  Arrival time at destination|  Cost of one ticket|"
	  "Number of tickets left for sale|  Number of tickets sold\n");
	printf("+--+-------------+---------------+-----------------+-----------------------------+--------------------+"
	  "-------------------------------+-----------------------+\n");
	for (int i = 0; i < trains_num; i++) {
	  struct train tr = trains[i];
    printf("|%2d|%13s|%15d.%d.%d|%17d.%d.%d|%29d.%d.%d : %d.%d.%d|%20d|%31d|%24d\n", i+1, tr.destination, tr.departureDay, tr.departureMonth,
	  tr.departureYear, tr.departureHour, tr.departureMinute, tr.departureSecond, tr.arrivalDay, tr.arrivalMonth,
	  tr.arrivalYear, tr.arrivalHour, tr.arrivalMinute, tr.arrivalSecond, tr.ticketPrice, tr.quantityOfRemainingTickets,
	  tr.quantityOfSoldTickets);   
	}
	printf("+--+-------------+---------------+-----------------+-----------------------------+--------------------+"
	  "-------------------------------+-----------------------+\n");
	printf("Enter 0 to return: ");
	int i;
	scanf("%d", &i);
	if (i == 0) {
	  return;
	}
  }
}

void doAddTrain(void) {
  system("cls");
  struct train tr;
  printf("Enter destination: ");
  scanf("%s", tr.destination);
  printf("Enter departure day: ");
  scanf("%d", tr.departureDay);
  printf("Enter departure month: ");
  scanf("%d", tr.departureMonth);
  printf("Enter departure year: ");
  scanf("%d", tr.departureYear);
  printf("Enter departure hour: ");
  scanf("%d", tr.departureHour);
  printf("Enter departure minute: ");
  scanf("%d", tr.departureMinute);
  printf("Enter departure second: ");
  scanf("%d", tr.departureSecond);
  printf("Enter arrival day: ");
  scanf("%d", tr.arrivalDay);
  printf("Enter arrival month: ");
  scanf("%d", tr.arrivalMonth);
  printf("Enter arrival year: ");
  scanf("%d", tr.arrivalYear);
  printf("Enter arrival hour: ");
  scanf("%d", tr.arrivalHour);
  printf("Enter arrival minute: ");
  scanf("%d", tr.arrivalMinute);
  printf("Enter arrival second: ");
  scanf("%d", tr.arrivalSecond);
  printf("Enter ticket price: ");
  scanf("%d", tr.ticketPrice);
  printf("Enter quantity of remaining tickets: ");
  scanf("%d", tr.quantityOfRemainingTickets);
  printf("Enter quantity of sold tickets: ");
  scanf("%d", tr.quantityOfSoldTickets);
}

void doEditTrain(void) {
  system("cls");
  int num;
  printf("Enter train number to edit: ");
  scanf("%d", &num);
  if (num > trains_num) {
  	return;
  }
  struct train tr;
  printf("Enter destination: ");
  scanf("%s", tr.destination);
  printf("Enter departure day: ");
  scanf("%d", tr.departureDay);
  printf("Enter departure month: ");
  scanf("%d", tr.departureMonth);
  printf("Enter departure year: ");
  scanf("%d", tr.departureYear);
  printf("Enter departure hour: ");
  scanf("%d", tr.departureHour);
  printf("Enter departure minute: ");
  scanf("%d", tr.departureMinute);
  printf("Enter departure second: ");
  scanf("%d", tr.departureSecond);
  printf("Enter arrival day: ");
  scanf("%d", tr.arrivalDay);
  printf("Enter arrival month: ");
  scanf("%d", tr.arrivalMonth);
  printf("Enter arrival year: ");
  scanf("%d", tr.arrivalYear);
  printf("Enter arrival hour: ");
  scanf("%d", tr.arrivalHour);
  printf("Enter arrival minute: ");
  scanf("%d", tr.arrivalMinute);
  printf("Enter arrival second: ");
  scanf("%d", tr.arrivalSecond);
  printf("Enter ticket price: ");
  scanf("%d", tr.ticketPrice);
  printf("Enter quantity of remaining tickets: ");
  scanf("%d", tr.quantityOfRemainingTickets);
  printf("Enter quantity of sold tickets: ");
  scanf("%d", tr.quantityOfSoldTickets);
}

void doDeleteTrain() {  
  system("cls");
  int num;
  printf("Enter train number to delete: ");
  scanf("%d", &num);
  if (num > trains_num) {
    return;
  } 
  printf("Are you sure you want to delete this train? (1 - Yes, 2 - No): ");
  int i;
  scanf("%d", &i);
  if (i != 0) {
  	int index = num - 1;
  	for (int i = index; i < trains_num - 1; i++) {
  	  trains[i] = trains[i = 1];
	}
	trains_num--;
	printf("Train deleted");
  }
}

void doTrains() {
  while(1) {
  	system("cls");
  	printf("0. Return\n");
  	printf("1. List trains\n");
  	printf("2. Add train\n");
  	printf("3. Edit train\n");
  	printf("4. Delete train\n");
  	int i;
  	printf("Select number: ");
  	scanf("%d", &i);
  	switch (i) {
  	  case 0:
  	  	return;
  	  case 1:
  	  	doListTrains();
  	  	break;
  	  case 2:
  	  	doAddTrain();
  	  	break;
  	  case 3:
  	  	doEditTrain();
  	  	break;
  	  case 4:
  	  	doDeleteTrain();
  	  	break;
	}
  }
}

//IndividualWork//

void doAdmin(void) {
  while (1) {
  	system("cls");
  	printf("1. Users\n");
  	printf("2. Trains\n");
  	printf("3. Exit\n");
  	int i;
  	printf("Select number: ");
  	scanf("%d", &i);
  	switch (i) {
  	  case 1:
  	  	doUsers();
  	  	break;
  	  case 2:
  	  	doTrains();
  	  	break;
  	  case 3:
  	  	return;
	}
  }
}

void doUser(void) {
  while (1) {
    system("cls");
    printf("1. Trains\n");
    printf("2. Exit\n");
    int i;
    printf("Select number: ");
    scanf("%d", i);
    switch (i) {
      case 1:
      	doTrains();
      	break;
      case 2:
      	return;
	}
  }
}

void doLogin(void) {
  char login[100];
  char password[100];
  printf("Login: ");
  scanf("%s", login);
  int i = findUser(login);
  if (i < 0) {
  	printf("User not found");
  	return;
  }
  struct user u = users[i];
  printf("Password: ");
  scanf("%s", password);
  if (strcmp(u.password, password) != 0) {
  	printf("Invalid password");
  	return;
  }
  if (u.role == ADMIN_ROLE) {
  	doAdmin();
  }
  else {
  	doUser();
  }
}

void createDefaultAdmin(void) {
  system("cls");
  struct user u = {"admin", "pass", ADMIN_ROLE};
  users[users_num++] = u;
  printf("New datebase with default admin created. Use 'admin' for login and 'pass' for password\n");
}

int main(void) {
    if (load()) {
        //file loaded successfully
        doLogin();
    } else {
        //file doesn't exist
        createDefaultAdmin();
    }
    save();
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
