import random
words=['WORLD','GOVERNMENT','WORK','TIME','COMPUTER','FATHER','MOTHER','SON','DAUGHTER','GREEN','BLUE','RED','WHITE','YELLOW','AEROPLANE','PROGRAMMING','LANGUAGE','CITIZENSHIP','SCHOLARSHIP','STEAMBOAT','RAFT','DISCIPLINE','INFORMATION','LEARNING','FRIENDSHIP','EARTH','CLOUD','PLANET','LIBERTY','MARTYR','SOVEREIGN','SUPREME','TIMELINE','SUNRISE','JOYFUL']
def play(game_words):
    print('\n\n')
    score=0
    for w in game_words:
        print('Arrange the letters to form a valid word:')
        print_random_word(w)
        if w==input('\n').upper():
            print('\n\nCorrect\n')
            score+=1
        else:
            print('\n\nWrong\n')
            score-=1
    else:
        print('Net Score is',score)
def get_randomint(l,u):
    if(u>0):
        r=random.randint(0,u)
        while True:
            r=random.randint(0,u)
            if r not in l:
                l.append(r)
                break
        return r
    
def get_game_words(length):
    game_words=[]
    n_list=[]
    for i in range(length):
        game_words.append(words[get_randomint(n_list,len(words)-1)])
    return game_words
def print_random_word(word):
    n_list=[]
    for c in range(len(word)):
        print(word[get_randomint(n_list,len(word)-1)],end='')