#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>

void set_random_seed();
int randn(int n);
void possible_solutions (int length, int num, std::vector<std::vector<int> > &possiblesolutionslist );

struct mm_code_maker{

  void init(int i_length, int i_num){
    length = i_length;
    num = i_num;
  }

  void generate_sequence(){
    for(int i = 0; i < length; i++){
      sequence.push_back(randn(num));
    }
  }

  void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
    std::vector<int> seq = sequence;
    std::vector<int> att = attempt;
    black_hits = 0;
    white_hits = 0;
    //Code to find black hits
    for(int i = 0; i < att.size(); i++){
      if(att[i]==seq[i]){
        black_hits++;
        seq[i]=-1;
        att[i]=-2;
      }
    }
    //Code to find white hits
    for(int i = 0; i < att.size(); i++){
      for(int j = 0; j < seq.size(); j++){
        if(att[i] == seq[j]){
          white_hits++;
          seq[j] = -1;
          j=seq.size();
        }
      }
    }
  }

  std::vector<int> sequence;
  int length;
  int num;

};

struct mm_solver{
  void init(int i_length, int i_num){
    length = i_length;
    num = i_num;
  }

  std::vector<std::vector<int> > possiblesolution;
  int length;
  int num;

  //Creates first attempt from random numbers
  void first_attempt(std::vector<int>& attempt){
    for (int i = 0; i<length; i++){
      attempt.push_back(randn(num));
    }
  }

  //Creates and attempt with the list of possible solutions
  void create_attempt(std::vector<int>& attempt){
    int k = std::rand() % possiblesolution.size();
    attempt = possiblesolution[k];
  }

  //Able to provide a reduced matrix containing vectors of possible solutions
  void learn(std::vector<int>& attempt, int black_hits, int white_hits){
    std::vector<std::vector<int> > test;

    for (int k = 0; k<possiblesolution.size(); k++){

      std::vector<int> tmp = possiblesolution[k];

      int black_hits2 = 0;
      int white_hits2 = 0;

      //Codes to compare new attempt (tmp) with previous attempt (attempt)

      //Code to find new black hits (black_hits2)
      for (int i = 0; i<tmp.size(); i++){
        for (int j = 0; j<tmp.size(); j++){
          if (attempt[i] == tmp[j] && i == j ){
            black_hits2++;
            tmp[j] = -1;
            j = tmp.size();
          }
        }
      }

      //Code to find new white hits (white_hits2)
      for (int i = 0; i<tmp.size(); i++){
        for(int j = 0; j<tmp.size(); j++){
          if(attempt[i] == tmp[j]){
            white_hits2++;
            tmp[j] = -1;
          }
        }
      }

      //If the new no of black hits/ white hits equals the previous no of black hits/ white hits
      //Then we add to a new reduced matrix of possible solutions (test)
      if (black_hits2==black_hits){
        test.push_back(possiblesolution[k]);
      }
    }

    possiblesolution = test;

    attempt[0] = possiblesolution.size();
  }

  //Creates a matrix containing vectors of possible solutions
  void possible_solutions (int length, int num, std::vector<std::vector<int> > possiblesolutionslist ){

    std::vector<int> empty (length);
    int total = std::pow(num, length);

    for (int i = 0; i<total; i++){
      possiblesolutionslist.push_back(empty);
    }

    for (int k = 0; k<length; k++){

      int g = 0;
      while(g<total){

        for (int i = 0; i < num; i++){

          for (int j = 0; j<std::pow(num, length-k-1); j++){
            possiblesolutionslist[g][k] = i;
            g++;
          }
        }
      }
    }

    possiblesolution = possiblesolutionslist;
  }

};

int main(){
  int length, num,times;
  int n = 0;
  std::cout << "enter length of sequence and number of possible values:" << std::endl;
  std::cin >> length >> num;
  std::cout << "how many times ?" << std::endl;
  std::cin >> times;

  std::vector<int> all_attempts;
  double avg=0;

  while(n<times){
    set_random_seed();
    std::vector<std::vector<int> > possibsol;

    mm_solver solver;
    solver.init(length, num);
    solver.possible_solutions(length, num, possibsol);

    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();

    int black_hits=0, white_hits=0;
    int attempts_limit = 5000;
    int attempts = 0;
    std::vector<int> attempt;
    while((black_hits < length) && (attempts < attempts_limit)){
      solver.create_attempt(attempt);
      maker.give_feedback(attempt, black_hits, white_hits);
      std::cout << "attempt: " << std::endl;
      for(int i = 0; i < attempt.size(); i++){
        std::cout << attempt[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << std::endl;
      solver.learn(attempt, black_hits, white_hits);
      attempts++;
    }

    if(black_hits == length){
        std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
    }
    else{
        std::cout << "after " << attempts << " attempts still no solution" << std::endl;
    }

    std::cout << "the sequence generated by the code maker was:" << std::endl;

    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }

    std::cout<< " "<<std::endl;
    n++;
    all_attempts.push_back(attempts);
  }


  for(int i=0; i<all_attempts.size(); i++){
    avg=avg+all_attempts[i];
  }
  avg=avg/all_attempts.size();

  std::cout<< "The avg is " << avg<<std::endl;

  return 0;
}

void set_random_seed(){
  std::srand(std::time(0));
}

int randn(int n){
  return std::rand() % n;
}
