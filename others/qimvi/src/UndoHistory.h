#pragma once

#include <deque>

// Zmuszam szablon, żeby przyjmował tylko typ wskaźnikowy.
template <typename T>
class UndoHistory;

/**
 * @brief Generyczna klasa przechowująca stany historii.
 */
template <typename T>
class UndoHistory<T*>

{
public:
	/**
	 * @brief Tworzy nową historię operacji.
	 * @param size Maksymalna ilość stanów jaka będzie zapamiętana.
	 */
	UndoHistory(int size) : size(size)
	{
	}

	/**
	 * @brief Sprząta pamięć z obiektów stanów.
	 */
	~UndoHistory()
	{
		while (!history.empty())
		{
			T* removed = history.back();
			history.pop_back();
			delete removed;
		}
	}

	/**
	 * @brief Dodaje nowy stan historii i ustawia go bieżącym.
	 */
	void push(T* element)
	{
		history.push_front(element);
		while (history.size() > size)
		{
			T* removed = history.back();
			history.pop_back();
			delete removed;
		}
		currentIndex = 0;
	}

	/**
	 * @brief Zwraca wskaźnik do bieżącego stanu historii.
	 */
	T* current()
	{
		return history.at(currentIndex);
	}

	/**
	 * @brief Informuje, czy cofnięcie operacji jest możliwe.
	 */
	bool isUndoPossible()
	{
		return !history.empty() && (currentIndex + 1) < history.size();
	}

	/**
	* @brief Informuje, czy ponowienie operacji jest możliwe.
	*/
	bool isRedoPossible()
	{
		return !history.empty() && (currentIndex - 1) >= 0;
	}

	/**
	* @brief Cofa ostatnią operację.
	*/
	void undo()
	{
		if (isUndoPossible()) currentIndex++;
	}

	/**
	 * @brief Ponawia ostatnio cofniętą operację.
	 */
	void redo()
	{
		if (isRedoPossible()) currentIndex--;
	}

private:
	int size;
	int currentIndex = 0;
	std::deque<T*> history;
};
