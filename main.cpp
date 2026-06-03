#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Node
{

public:
    char bukva;
    Node* next;

    Node(char bukva)
    {
        this->bukva = bukva;
        this->next = NULL;
    }
}; // класс, определяющий конкретный объект

class list
{

public:

    Node* head; // начало списка
    Node* tail; // конец списка

    list()
    {
        this->head = NULL;
        this->tail = NULL;
    } // предварительно голове и концу списка присвоим NULL

    void pop()
    {
        if(head == NULL) return;

        if(head == tail)
        {
            delete tail;
            head = NULL;
            tail = NULL;
            return;
        }

        Node* node = head;
        head = node->next;
        delete node;

    } // метод для удаления всех элементов списка

    Node* getAt(int k)
    {
        if(k<0) return NULL;

        Node* node = head;

        int n=0;

        while(node && n!=k && node->next)
        {
            node = node->next;
            n++;
        }

        if(n==k)
        {
            return node;
        }

        return NULL;
    } // поиск элемента по индексу

    void push_nazv(char bukva)
    {
        Node* node = new Node(bukva);
        node->next = head;
        head = node;

        if(tail == NULL) tail = node;
    } // добавление "головы списка"

    void push_backi(char bukva)
    {
        Node* node = new Node(bukva);

        if(head == NULL) head = node;
        if(tail != NULL) tail->next = node;

        tail = node;

    } // добавление элемента в конец списка

    void insert(int k,char bukva)
    {
        Node* left = getAt(k);
        
        if(left == NULL) return;

        Node* right = left->next;
        Node* node = new Node(bukva);

        left->next = node;
        node->next = right;

        if(right == NULL) tail = node;
    } // добавление элемента посреди дргуих внутри списка

    void pop2(int k)
    {
        if(k<0) return;

        if(k==0)
        {
            pop();
            return;
        }

        Node* left = getAt(k-1);
        Node* node = left->next;

        if(node == NULL) return;

        Node* right = node->next;

        left->next = right;

        if(node == tail) tail = left;

        delete node;
    } // удаление элемента по индексу

    void print()
    {
        cout<<head->bukva<<" = ";

        cout<<"{";

        for(Node* node = (head->next);node;node=node->next)
        {
            cout<<node->bukva;

            if(node->next)
            {
                cout<<",";
            }
        }

        cout<<"}";

        cout<<"\n";
    } // метод для вывода множества

}; // класс для работы со списком в целом

vector<char> elements(list s)
{
    vector<char> el;

    for(Node* node=(s.head)->next;node;node=node->next)
    {
        el.push_back(node->bukva);
    }

    return el;
} // функция, которая добавляет в вектор элементы списка

void print_vector(vector<char> zxc)
{
    cout<<"{";
    for(int i=0;i<zxc.size();i++)
    {
        if(i!=zxc.size()-1) cout<<zxc[i]<<",";
        else cout<<zxc[i];
    }
    cout<<"}\n";
}

bool proverka1(char nazv,vector<list> sets)
{
    bool flag=true;

    for(list x: sets)
    {
        if((x.head)->bukva==nazv)
        {
            flag=false;
            break;
        }
    }

    return flag;
}

bool proverka2(char a,char b,vector<list> sets)
{
    bool flag1=false;

    for(list x: sets)
    {
        if((x.head)->bukva==a)
        {
            flag1=true;
            break;
        }
    }

    bool flag2=false;

    for(list x: sets)
    {
        if((x.head)->bukva==b)
        {
            flag2=true;
            break;
        }
    }

    return flag1 && flag2;
}

int main()
{
    vector<list> sets; // вектор, в котором будем хранить все множества

    cout<<"Здравствуйте, это программа для работы со множествами!\n";
    cout<<"Вот набор команд, которым вы можете распоряжаться:\n";
    cout<<"1. new A (добавить новое множество с именем A)\n";
    cout<<"2. del A(полностью удалить множество)\n";
    cout<<"3. add A x(добавить элемент x в множество A)\n";
    cout<<"4. rem A x(удалить элемент x из множества A)\n";
    cout<<"5. pow A(вычислить булеан множества A)\n";
    cout<<"6. see[A](с аргументом вывести множество, без аргумента - все множества)\n";
    cout<<"7. A+B(объединение множеств)\n";
    cout<<"8. A&B(пересечение множеств)\n";
    cout<<"9. A-B(разность множеств)\n";
    cout<<"10. A<B(проверка на подмножество)\n";
    cout<<"11. A=B(проверка на равенство)\n";
    cout<<"12. exit(Завершить работу)\n";

    while(true)
    {
        int var;
        cout<<"Введите номер команды: ";
        cin>>var;

        if(var==1)
        {
            char nazv;
            cout<<"Введите название множества, которое хотите создать: ";
            cin>>nazv;

            bool flag=true;

            for(list x: sets)
            {
                if((x.head)->bukva==nazv)
                {
                    flag=false;
                    break;
                }
            }

            if(!flag) cout<<"Множество с таким названием уже существует!\n";

            else
            {
                list A;
                A.push_nazv(nazv);
                sets.push_back(A);
            }
        } // добавление множества

        if(var==2)
        {
            char nazv;
            cout<<"Введите название множества, которое хотите удалить: ";
            cin>>nazv;

            if(proverka1(nazv,sets)) cout<<"Множества с таким названием не существует!\n";

            else
            {
                int k=0;

                for(list x: sets)
                {
                    if((x.head)->bukva==nazv)
                    {
                        while(x.head) x.pop();
                        sets.erase(sets.begin()+k);
                    }

                    k++;
                }
            }

        } // удаление множества

        if(var==3)
        {
            char nazv;
            cout<<"Введите название множества, в которое хотите добавить элемент: ";
            cin>>nazv;

            char el;
            cout<<"Введите символ, который хотите добавить: ";
            cin>>el;

            vector<char> T;

            for(list w: sets)
            {
                if(w.head->bukva==nazv)
                {
                    T=elements(w);
                    break;
                }
            }

            bool flag=true;

            for(char m: T)
            {
                if(m==el)
                {
                    flag=false;
                    break;
                }
            }

            if(proverka1(nazv,sets)) cout<<"Множества с таким названием не существует!\n";
            else if(!flag) cout<<"Такой элемент уже есть в множестве!\n";

            else
            {
                for(int i=0;i<sets.size();i++)
                {
                    if((sets[i].head)->bukva==nazv)
                    {
                        if(sets[i].head==sets[i].tail) sets[i].push_backi(el);
                        else if((sets[i].tail->bukva)<=el) sets[i].push_backi(el);

                        else
                        {
                            int index=0;

                            for(Node* node=sets[i].head;node;node=node->next)
                            {
                                if((node->bukva)>=el)
                                {
                                    sets[i].insert(index-1,el);
                                    break;
                                }
 
                                index++;
                            }
                        }
                    }
                }

            }
        } // добавление элемета в множество

        if(var==4)
        {
            char nazv;
            cout<<"Введите название множества, из которого хотите удалить элемент: ";
            cin>>nazv;

            char el;
            cout<<"Введите символ, который хотите удалить: ";
            cin>>el;

            if(proverka1(nazv,sets)) cout<<"Множества с таким названием не существует!\n";

            else
            {
                for(int i=0;i<sets.size();i++)
                {
                    if(((sets[i].head)->bukva)==nazv)
                    {
                        int cnt=0; // счетчик, с помощью которого определяется индекс элемента, который нужно удалить

                        for(Node* node = sets[i].head;node;node=node->next)
                        {
                            if((node->bukva)==el) break;
                            cnt++;
                        }
                        sets[i].pop2(cnt); // удаляем элемент по индексу
                    }
                }
            }
        } // удаление элемента из множества

        if(var==5)
        {
            char nazv;
            cout<<"Введите название множества, булеан которого хотите вывести: ";
            cin>>nazv;

            if(proverka1(nazv,sets)) cout<<"Множества с таким названием не существует!\n";

            else
            {
                vector<char> el;

                for(list x: sets)
                {
                    if((x.head)->bukva==nazv) el=elements(x);
                }

                int n=el.size();
                unsigned int powSetSize = 1 << n; 
                cout << "{ " << endl;

                for (unsigned int i = 0; i < powSetSize; ++i) 
                {
                    cout << "  {";
                    bool first = true;

                    // Проверяем каждый бит числа 'i'
                    for (int j = 0; j < n; ++j) 
                    {
                        // Если j-й бит равен 1, то выводим j-й элемент массива
                        if ((i & (1 << j)) != 0) {
                            if (!first) {
                            cout << ", ";
                        }

                        cout << el[j];
                        first = false;

                        }
                    }

                    cout << "}" << (i + 1 < powSetSize ? "," : "") << endl;
                }

                cout << "}" << endl;
            }
        }

        if(var==6)
        {
            cout<<"Напишите see, если хотите вывести все множества сразу, иначе напишите see[название множества, которое хотите вывести]: ";
            string see;
            cin>>see;

            if(see=="see")
            {
                for(list x: sets) x.print();
            }

            else if(!(see[0]=='s' && see[1]=='e' && see[2]=='e' && see[3]=='[' && (see[4]>=65 && see[4]<=90) && see[5]==']')) cout<<"Функция введена неправильно!\n";

            else
            {
                /*char nazv;
                cout<<"Введите название множества, которое хотите вывести: ";
                cin>>nazv;*/

                bool flag=true;

                for(list x: sets)
                {
                    if((x.head)->bukva==see[4])
                    {
                        flag=false;
                        break;
                    }
                }

                if(flag) cout<<"Множества с таким названием не существует!\n";

                else
                {
                    for(list x: sets)
                    {
                        if((x.head)->bukva==see[4]) x.print();
                    }
                }
            }
        }

        if(var==7)
        {
            char a,b;
            cout<<"Введите множества, для которых хотите найти объединение(через пробел): ";
            cin>>a>>b;

            if(!proverka2(a,b,sets)) cout<<"Ошибка! Не все множества существуют!\n";

            else
            {
                vector<char> el_a;
                vector<char> el_b; // вектора элементов множеств
                vector<char> obedinenie; // вектор элементов объединения

                for(list x: sets)
                {
                    if((x.head)->bukva==a) el_a=elements(x);
                    if((x.head)->bukva==b) el_b=elements(x);
                }

                for(char z: el_a)
                {
                    obedinenie.push_back(z);
                }

                for(char h: el_b)
                {
                    bool flag=true;

                    for(char q: obedinenie)
                    {
                        if(q==h)
                        {
                            flag=false;
                            break;
                        }
                    }

                    if(flag) obedinenie.push_back(h);
                    sort(obedinenie.begin(),obedinenie.end());
                }


                cout<<a<<"+"<<b<<" = ";
                print_vector(obedinenie);
            }
        } // нахождение объединения

        if(var==8)
        {
            char a,b;
            cout<<"Введите множества, для которых хотите найти пересечение(через пробел): ";
            cin>>a>>b;

            if(!proverka2(a,b,sets)) cout<<"Ошибка! Не все множества существуют!\n";

            else
            {
                vector<char> el_a;
                vector<char> el_b; // вектора элементов множеств
                vector<char> peresechenie; // вектор элементов пересечения

                for(list x: sets)
                {
                    if((x.head)->bukva==a) el_a=elements(x);
                    if((x.head)->bukva==b) el_b=elements(x);
                }

                for(char e: el_a)
                {
                    bool flag=false;

                    for(char t: el_b)
                    { 
                        if(e==t)
                        {
                            flag=true;
                            break;
                        }
                    }

                    if(flag) peresechenie.push_back(e);
                }

                sort(peresechenie.begin(),peresechenie.end());

                cout<<a<<"&"<<b<<" = ";
                print_vector(peresechenie);
            }
        } // нахождение пересечения

        if(var==9)
        {
            char a,b;
            cout<<"Введите множества, для которых хотите найти разность(через пробел): ";
            cin>>a>>b;

            if(!proverka2(a,b,sets)) cout<<"Ошибка! Не все множества существуют!\n";

            else
            {
                vector<char> el_a;
                vector<char> el_b; // вектора элементов множеств
                vector<char> razn; // вектор элементов разности

                for(list x: sets)
                {
                    if((x.head)->bukva==a) el_a=elements(x);
                    if((x.head)->bukva==b) el_b=elements(x);
                }

                for(char g: el_a)
                {
                    bool flag=true;

                    for(char p: el_b)
                    {
                        if(g==p)
                        {
                            flag=false;
                            break;
                        }
                    }

                    if(flag) razn.push_back(g);
                }

                sort(razn.begin(),razn.end());

                cout<<a<<"-"<<b<<" = ";
                print_vector(razn);
            }

        } // нахождение разности

        if(var==10)
        {
            char a,b;
            cout<<"Введите множества, для которых хотите сделать проверку на подмножество(через пробел, сначала множество проверяемое на подмножество): ";
            cin>>a>>b;

            if(!proverka2(a,b,sets)) cout<<"Ошибка! Не все множества существуют!\n";

            else
            {
                vector<char> el_a;
                vector<char> el_b; // вектора элементов множеств

                for(list x: sets)
                {
                    if((x.head)->bukva==a) el_a=elements(x);
                    if((x.head)->bukva==b) el_b=elements(x);
                }

                sort(el_a.begin(),el_a.end());
                sort(el_b.begin(),el_b.end());
            
                if(el_a.size()>el_b.size()) cout<<"Множество "<<a<<" не является подмножеством "<<b<<"!\n";

                else
                {
                    int k=0;

                    for(int i=0;i<el_a.size();i++)
                    {
                        if(el_a[i]==el_b[i]) k++;
                    }

                    if(k==el_a.size()) cout<<"Множество "<<a<<" является подмножеством "<<b<<"\n";
                    else cout<<"Множество "<<a<<" не является подмножеством "<<b<<"!\n";
                }
            }
        } // проверка на подмножество

        if(var==11)
        {
            char a,b;
            cout<<"Введите множества, для которых хотите сделать проверку на равенство(через пробел): ";
            cin>>a>>b;

            if(!proverka2(a,b,sets)) cout<<"Ошибка! Не все множества существуют!\n";

            else
            {
                vector<char> el_a;
                vector<char> el_b; // вектора элементов множеств

                for(list x: sets)
                {
                    if((x.head)->bukva==a) el_a=elements(x);
                    if((x.head)->bukva==b) el_b=elements(x);
                }

                if(el_a.size()!=el_b.size()) cout<<"Множества не равны!\n";

                else
                {
                    int k=0;

                    for(int i=0;i<el_a.size();i++)
                    {
                        if(el_a[i]==el_b[i]) k++;
                    }

                    if(k==el_a.size()) cout<<"Множества равны\n";
                    else cout<<"Множества не равны!\n";
                }
            }
        } // проверка на равенство

        if(var==12) break;// условие окончания работы
    } // цикл для работы пользователя до тех пор пока он сам не захочет остановиться

    return 0;
}