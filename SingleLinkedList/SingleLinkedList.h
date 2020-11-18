#pragma once
#include <ostream>

template <typename T> class SingleLinkedList;
template <typename T> class LinkedListIterator;

template <typename T>
class SingleLinkedList
{
public:
    SingleLinkedList();
    ~SingleLinkedList();

    void Add(const T& value);

    LinkedListIterator<T> cbegin() const;
    LinkedListIterator<T> cend() const;

    friend std::ostream& operator<<(std::ostream& out, const SingleLinkedList& list)
    {
        auto current = list.head;
        out << "{ ";
        while (current->next != nullptr)
        {
            out << *current << ", ";
            current = current->next;
        }
        return out << *current << " }";
    }

    class ListItem
    {
    public:
        explicit ListItem(const T& value);
        ~ListItem();

        T value;
        ListItem* next;

        friend std::ostream& operator<<(std::ostream& out, const ListItem& item)
        {
            return out << item.value;
        }
    };

private:
    ListItem* head;
    ListItem* tail;
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList()
    : head(nullptr), tail(nullptr)
{
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    auto current = this->head;
    while (current != nullptr)
    {
        auto temp = current->next;
        delete current;
        current = temp;
    }
}

template <typename T>
void SingleLinkedList<T>::Add(const T& value)
{
    auto item = new ListItem(value);
    if (this->head == nullptr)
    {
        this->head = item;
        this->head->next = this->tail;
        this->tail = item;
        return;
    }

    this->tail->next = item;
    this->tail = item;
}

template <typename T>
LinkedListIterator<T> SingleLinkedList<T>::cbegin() const
{
    return LinkedListIterator<T>(this->head);
}

template <typename T>
LinkedListIterator<T> SingleLinkedList<T>::cend() const
{
    auto result = this->tail;
    if (result != nullptr)
    {
        result = result->next;
    }
    return LinkedListIterator<T>(result);
}

template <typename T>
SingleLinkedList<T>::ListItem::ListItem(const T& value)
    : value(value), next(nullptr)
{
}

template <typename T>
SingleLinkedList<T>::ListItem::~ListItem() = default;

template <typename T>
class LinkedListIterator
{
public:
    LinkedListIterator(const LinkedListIterator<T>& other);
    ~LinkedListIterator();

    bool operator!=(const LinkedListIterator<T>& other) const;
    bool operator==(const LinkedListIterator<T>& other) const;
    T& operator*() const;
    LinkedListIterator operator++();

private:
    friend class SingleLinkedList<T>;

    explicit LinkedListIterator(typename SingleLinkedList<T>::ListItem* item)
        : item(item)
    {
    }

    typename SingleLinkedList<T>::ListItem* item;
};

template <typename T>
LinkedListIterator<T>::LinkedListIterator(const LinkedListIterator<T>& other)
{
    this->item = other.item;
}

template <typename T>
LinkedListIterator<T>::~LinkedListIterator() = default;

template <typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& other) const
{
    return this->item != other.item;
}

template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& other) const
{
    return this->item == other.item;
}

template <typename T>
T & LinkedListIterator<T>::operator*() const
{
    return this->item->value;
}

template <typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator++()
{
    if (this->item != nullptr)
    {
        this->item = this->item->next;
    }
    return LinkedListIterator<T>(this->item);
}
