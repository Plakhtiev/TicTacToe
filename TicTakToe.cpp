#include <iostream>

class Cell {
public:
	Cell(int pos) {
		m_pos = pos;
	}

	Cell(char player, int pos)
	{
		m_player = player;
		m_pos = pos;
	};

	char GetPlayer()
	{
		return m_player;
	};

	int GetPos() {
		return m_pos;
	}

	void SetPlayer(char player) {
		m_player = player;
	}

	bool CellExists() {
		m_player ? true : false;
	}

	void SetPos(int pos) {
		m_pos = pos;
	}

private:
	int m_pos;
	char m_player = ' ';
};

class TikTakToe
{
public:
	TikTakToe()
	{
		for (int i = 0; i < sizeof(m_field) / sizeof(Cell*); ++i) {
			m_field[i] = new Cell(i);
		}
	}

	void Show()
	{
		for (int i = 0; i < sizeof(m_field) / sizeof(Cell*); ++i) {
			std::cout << "|" << m_field[i]->GetPlayer();
			if (i == 2 || i == 5 || i == 8) {
				std::cout << "|" << std::endl;
			}
		}
	}

	void Game() {
		int movePos;
		Show();
		if (m_currPlayer == 'x') {
			std::cout << "Move player " << m_currPlayer << ". Enter your move from 0 to 8" << std::endl;
			std::cin >> movePos;
			move(m_currPlayer, movePos);
			m_currPlayer = '0';
			
		}
		else {
			std::cout << "Move player " << m_currPlayer << ". Enter your move from 0 to 8" << std::endl;
			std::cin >> movePos;
			move(m_currPlayer, movePos);
			m_currPlayer = 'x';
		}

		

		if (CheckWinner('x') || CheckWinner('0')) {
			Show();
			return;
		}
		Game();
	}

	Cell GetCell(int cell) {
		return *m_field[cell];
	}

	~TikTakToe()
	{
		for (int i = 0; i < sizeof(m_field) / sizeof(Cell*); ++i) {
			delete m_field[i];
		}
	}

private:
	Cell* m_field[9] = {};
	char m_currPlayer = 'x';

	void move(char player, int pos) {
		if (pos > 8 || pos < 0) {
			std::cout << "Incorrect position. Try again" << std::endl;
			std::cin >> pos;
		}
		if (m_field[pos]->GetPlayer() == ' ' && pos <= 8 && pos >= 0) {
			m_field[pos]->SetPlayer(player);
			return;
		}
		else if (m_field[pos]->GetPlayer() == '0' || m_field[pos]->GetPlayer() == 'x') {
			std::cout << "The cell belongs to another player. Try again" << std::endl;
			std::cin >> pos;
		}

		move(player, pos);
		return;
	}

	bool CheckFrontHor(int pos, char player) {
		return (m_field[pos]->GetPlayer() == player &&
			m_field[pos + 1]->GetPlayer() == player &&
			m_field[pos + 2]->GetPlayer() == player);
	}

	bool CheckFrontVer(int pos, char player) {
		return (m_field[pos]->GetPlayer() == player &&
			m_field[pos + 3]->GetPlayer() == player &&
			m_field[pos + 6]->GetPlayer() == player);
	}

	bool CheckDiagL(int pos, char player) {
		return (m_field[pos]->GetPlayer() == player &&
			m_field[pos + 4]->GetPlayer() == player &&
			m_field[pos + 8]->GetPlayer() == player);
	}

	bool CheckDiagR(int pos, char player) {
		return (m_field[pos]->GetPlayer() == player &&
			m_field[pos + 2]->GetPlayer() == player &&
			m_field[pos + 4]->GetPlayer() == player);
	}

	bool CheckWinner(char player) {
		if (CheckDiagL(0, player) || CheckDiagR(2, player) || CheckFrontHor(0, player) || CheckFrontVer(0, player)
			|| CheckFrontHor(3, player) || CheckFrontVer(1, player) || CheckFrontHor(6, player) || CheckFrontVer(2, player)) {
			std::cout << player << " - " << "WIN!"<< std::endl;
			return true;
		}
		return false;
	}
};

int main()

{
	TikTakToe field;
	field.Game();
}