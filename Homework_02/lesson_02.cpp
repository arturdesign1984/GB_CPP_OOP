#include <cstdint>
#include <iostream>

// 01 //////////////////////////////

class Person
{
private:
    std::string name;
    uint16_t age;
    char sex;
    uint16_t weight;
public:
    Person (std::string na, uint16_t ag, char se, uint16_t we) : name(na), age(ag), sex(se), weight(we)
    {}
    void setName(std::string name)
    {
        this->name = name;
    }
    void setAge(uint16_t age)
    {
        this->age = age;
    }
    void setSex(char sex)
    {
        this->sex = sex;
    }
    void setWeight(uint16_t weight)
    {
        this->weight = weight;
    }
    std::string getName()
    {
        return name;
    }
    uint16_t getAge()
    {
        return age;
    }
    char getSex()
    {
        return sex;
    }
    uint16_t getWeight()
    {
        return weight;
    }
};

class Student : public Person
{
private:
    static uint16_t studentsCount;
    uint16_t educationYear;
public:
    Student (std::string na, uint16_t ag, char se, uint16_t we, uint16_t ed) : Person(na, ag, se, we), educationYear(ed)
    {
        studentsCount++;
    }
    void setEducationYear(uint16_t educationYear)
    {
        this->educationYear = educationYear;
    }
    uint16_t getEducationYear()
    {
        return educationYear;
    }
    void upEducationYear()
    {
        educationYear++;
    }
    void print()
    {
        std::cout << "Name: " << getName() <<" | Age: " << getAge() << " | Sex: " << getSex() <<
                     " | Weight: " << getWeight() << " | Education year: " << getEducationYear() << std::endl;
    }
    void printNomberOfStudents()
    {
        std::cout << "Nomber of students: " << studentsCount << std::endl;
    }
    ~Student()
    {
        studentsCount--;
    }
};
uint16_t Student::studentsCount = 0;
// 02 //////////////////////////////

class Fruit
{
private:
    std::string name;
    std::string color;
public:
    void setName(std::string name)
    {
        this->name = name;
    }
    void setColor(std::string color)
    {
        this->color = color;
    }
    std::string getName()
    {
        return name;
    }
    std::string getColor()
    {
        return color;
    }
};

class Apple : public Fruit
{
public:
    Apple()
    {}
    Apple(std::string col)
    {
        setName("apple");
        setColor(col);
    }
};

class Banana : public Fruit
{
public:
    Banana()
    {
        setName("banana");
        setColor("yellow");
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith()
    {
        setName("Granny Smith apple");
        setColor("green");
    }
};

// 03 //////////////////////////////

/*

  class Game                                // Игра
  {};
  class Card                                // Карта
  {};
  class Hand                                // Набор карт
  {};
  class Deck : public Hand                  // Раздача
  {};
  class GenericPlayer : public Hand         // Обобщенный игрок
  {};
  class Player : public GenericPlayer       // Человек
  {};
  class House : public GenericPlayer        // Компьютер
  {};

*/
int main()
{
    // 01 //////////////////////////////
    std::cout << "######\n# 01 #\n######\n\nClass Student:\n\n";

    Student s1("Anton", 18, 'M', 60, 2);
    Student s2("Boris", 17, 'M', 90, 1);
    Student s3("Eva", 20, 'F', 55, 4);

    s1.printNomberOfStudents();

    std::cout << std::endl;

    s1.print();
    s2.print();
    s3.print();

    std::cout << std::endl;

    // 02  /////////////////////////////
    std::cout << "######\n# 02 #\n######\n\nClass Fruit:\n\n";

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    std::cout << std::endl;

 
    return 0;
}

