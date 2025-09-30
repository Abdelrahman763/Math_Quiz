
// notes  
// 1- i must intialize char variable with any letter ot a space instead => char OperationSign = ' ';
// 2- i can intialize string variable wihout any space or even word => string AnswerStatusWord = "";
// 3-  i Changed the variable name to avoid conflict with the function name => short level = QuestionLevel();
// if i put cout<< before system("color 2F"); => it will print zero after color effecting

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    short Number1 = 0;
    short Number2 = 0;
    enOperationType Optype;
    enQuestionLevel QuestionLevel;
    short PlayerAnswer = 0;
    short CorrectAnswer = 0;
    bool AnswerResult = true;
};

struct stQuizz
{
    stQuestion QuestionsList[100];
    short NumberOfQuestions = 0;
    enQuestionLevel QuestionLevel;
    enOperationType Optype;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = true;
};

short ReadNumberOfQuestions()
{
    short number;
    do
    {
        cout << "enter the number of questions : ";
        cin >> number;
    } while (number < 1 || number > 10);
    
    return number;
}

enQuestionLevel ReadQuestionLevel()
{
    short number;
    do
    {
        cout << "\nenter question level [1] Easy , [2] Med , [3] Hard , [4] Mix ? : ";
        cin >> number;
    } while (number < 1 || number > 4);

    return (enQuestionLevel)number;
}

enOperationType ReadOerationType()
{
    short number;
    do
    {
        cout << "\nenter operation type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? : ";
        cin >> number;
    } while (number < 1 || number > 5);

    return (enOperationType)number;
}

short Random(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

short CalculateCorrectAnswer(stQuestion Question)
{
    switch (Question.Optype)
    {
    case Add:
        return Question.Number1 + Question.Number2;
    case Sub:
        return Question.Number1 - Question.Number2;
    case Mul:
        return Question.Number1 * Question.Number2;
    case Div :
        return Question.Number1 / Question.Number2;
    default:
        return Question.Number1 + Question.Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)Random(1, 3);

    if (OpType == enOperationType::MixOp)
        OpType = (enOperationType)Random(1, 4);
   
    Question.Optype = OpType;

    switch (QuestionLevel)
    {
    case Easy:
        Question.Number1 = Random(1, 10);
        Question.Number2 = Random(1, 10);

        Question.CorrectAnswer = CalculateCorrectAnswer(Question);

        Question.QuestionLevel = QuestionLevel;
        
        return Question;
        break;

    case Mid:
        Question.Number1 = Random(10, 50);
        Question.Number2 = Random(10, 50);

        Question.CorrectAnswer = CalculateCorrectAnswer(Question);

        Question.QuestionLevel = QuestionLevel;

        return Question;
        break;
        
    case Hard:
        Question.Number1 = Random(50, 100);
        Question.Number2 = Random(50, 100);

        Question.CorrectAnswer = CalculateCorrectAnswer(Question);

        Question.QuestionLevel = QuestionLevel;

        return Question;
        break;

    default :
        Question.Number1 = Random(1, 10);
        Question.Number2 = Random(1, 10);

        Question.CorrectAnswer = CalculateCorrectAnswer(Question);

        Question.QuestionLevel = QuestionLevel;

        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz & Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuestionLevel , Quizz.Optype);
    }


}

short ReadUserAnswer()
{
    int number;
    cin >> number;
    return number;
}

char GetOperationSymbol(enOperationType OperationType)
{
    char ArrOfOperators[] = { '+' , '-' , '*' , '/' };
    return ArrOfOperators[OperationType-1];
}

void PrintQuestion(stQuizz & Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionsList[QuestionNumber].Number1 << " ";
    cout << GetOperationSymbol(Quizz.QuestionsList[QuestionNumber].Optype) << " ";
    cout << Quizz.QuestionsList[QuestionNumber].Number2 << "\n";
    cout << "------------------------------\n";
}

void CorrectTheQuestionAnswer(stQuizz & Quizz, short QuestionNumber)
{
    if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer != Quizz.QuestionsList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "\nWrong Answer :(\n";
        cout << "The right answer is : " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer << "\n";
        system("color 4F");
        cout << "\a";
    }

    else
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "\nRight Answer :)\n";
        system("color 2F");
    }
}

void AskAndCorrectQuestionListAnswer(stQuizz & Quizz)
{
    for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz, QuestionNumber);

        Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadUserAnswer();

        CorrectTheQuestionAnswer(Quizz , QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
    
}

string GetFinalResultsText(bool FinalResults)
{
    if (FinalResults)
        return "Pass";
    else
        return "Fail";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string ArrQuestionLevel[] = { "Easy" , "Med" , "Hard" , "Mix" };
    return ArrQuestionLevel[QuestionLevel - 1];
}

string GetOperationTypeText(enOperationType OperationType)
{
    string ArrOperators[] = { "Add" , "Sub" , "Mul" , "Div" ,"Mix" };
    return ArrOperators[OperationType - 1];
}


void SetColor(bool Pass)
{
    if (Pass)
        system("color 2F");
    else
        system("color 4F");
}

void PrintQuizResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "--------------------------------\n\n";
    cout << "Final Result is : " << GetFinalResultsText(Quizz.IsPass);
    cout << "\n\n--------------------------------\n\n";
    cout << "Number of questions : " << Quizz.NumberOfQuestions << "\n";
    cout << "Question Level is : " << GetQuestionLevelText(Quizz.QuestionLevel) << "\n";
    cout << "Operation Type is : " << GetOperationTypeText(Quizz.Optype) << "\n";
    cout << "Number of Right answers is : " << Quizz.NumberOfRightAnswers << "\n";
    cout << "Number of wrong answers is : " << Quizz.NumberOfWrongAnswers << "\n";
    cout << "----------------------------------------\n";
    
    SetColor(Quizz.IsPass);
}

void StartQuizz()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadNumberOfQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.Optype = ReadOerationType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizResults(Quizz);
}

void Reset()
{
    system("cls");
    system("color 0F");
}

void Start()
{
    char UserDecision = 'y';
    do 
    {
        Reset();
        StartQuizz();
        cout << "Do you want to play agian ? (y/n)\n";
        cin >> UserDecision;
    } while (UserDecision == 'y' || UserDecision == 'Y');
}

int main()
{
     srand((unsigned)time(NULL));
     Start();
}

