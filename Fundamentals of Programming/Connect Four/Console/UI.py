class UI:
    def __init__(self, gameController):
        self.__gameController = gameController

    def __start_new_game(self):
        self.__gameController.start_new_game()

    def __show_grid(self):
        grid = self.__gameController.get_grid()
        for index in range(6):
            print(index + 1, end=" ")
        print(7)
        for index1 in range(6):
            for index2 in range(6):
                print(grid[index1][index2], end=" ")
            print(grid[index1][6])

    def start_application(self):
        self.__start_new_game()
        choice = 'yes'
        while True:
            gridFull = self.__gameController.check_if_grid_full()
            if gridFull:
                print("The game ended in a draw!")
                break
            else:
                if choice == 'no':
                    print("Do you want to restart the game?(yes/no)")
                    anotherChoice = input("Your choice is: ")
                    if anotherChoice == 'no':
                        print("You exited the game. Nobody won.")
                        break
                    else:
                        self.__start_new_game()
                        choice = 'yes'
                else:
                    self.__gameController.place_computer_piece()
                    winner = self.__gameController.get_game_winner()
                    if winner == 2:
                        self.__show_grid()
                        print("The computer won!")
                        break
                    self.__show_grid()
                    column = input("Please input a column: ")
                    try:
                        column = int(column)
                        self.__gameController.place_player_piece(column - 1)
                        winner = self.__gameController.get_game_winner()
                        if winner == 1:
                            print("You won! Congratulations!")
                            break
                    except ValueError as valueError:
                        print(valueError)
                    print("Do you want to continue the game? (yes/no)")
                    choice = input("Your choice is: ")
                    choice.lower()
