# The base of this program comes from this video https://youtu.be/CkkjXTER2KE?si=oQ6ga19D9s1fTZh8
# My modifications:
# -Gave the chatbot a database of dialouge it can pick from (so the user doesn't have to enter every answer in manually)
# -Gave the user the ability to overwrite the chatbot's saved answers
# -Adjusted the accuracy of the answers
# With these modifications, the chatbot should have responses to many basic questions
# Citation for dialogue:
# Yanran Li, Hui Su, Xiaoyu Shen, Wenjie Li, Ziqiang Cao, and Shuzi Niu. 2017. DailyDialog: A Manually Labelled Multi-turn Dialogue Dataset. In Proceedings of the Eighth International Joint Conference on Natural Language Processing (Volume 1: Long Papers), pages 986–995, Taipei, Taiwan. Asian Federation of Natural Language Processing.



import json
from difflib import get_close_matches #used so that the string entered doesn't have to exactly match the one in the database

def load_knowledge_base(file_path: str) -> dict: #creates a dictionary from the database
    with open(file_path, 'r') as file:
        data: dict = json.load(file)
    return data

def save_knowledge_base(file_path: str, data: dict): #saves the dictionary to the database
    with open(file_path, 'w') as file:
        json.dump(data, file, indent=2)

def find_best_match(user_question: str, questions: list[str]) -> str | None: #finds the best match to the given string 
    matches: list = get_close_matches(user_question, questions, n=1, cutoff=0.7) #cutoff can be adjusted to give more accurate or frequent answers
    return matches[0] if matches else None


def get_answer_for_question(question: str, knowledge_base: dict) -> str | None: #returns the answer for the given question
    for q in knowledge_base["questions"]:
        if q["question"] == question:
            return q["answer"]

def chat_bot():
    knowledge_base: dict = load_knowledge_base('knowledge_base.json') #get dictionary of question-answer pairs
    user_input = None;
    while True:
        last = user_input #needed to keep track of last input if the user wants to overwrite it
        user_input: str = input('You: ')

        if user_input.lower() == 'quit': #user enters 'quit' to exit the program
            break

        if user_input.lower() == 'overwrite': #user enters 'overwrite' to overwrite the answer to their most recent question
                best_match: str | None = find_best_match(last, [q["question"] for q in knowledge_base["questions"]]) #this is where last is used
                index = None;
                for i, q in enumerate(knowledge_base["questions"]): #find the question in the dictionary
                    if q["question"] == best_match:
                        index = i;
                        break;
                new_answer: str = input('Bot: Type in the right answer: ')
                knowledge_base["questions"][index]["answer"] = new_answer #overwrite the answer
                save_knowledge_base('knowledge_base.json', knowledge_base) #save knowledge base
                print('Bot: Thank you! I learned a new response.')

        best_match: str | None = find_best_match(user_input, [q["question"] for q in knowledge_base["questions"]])

        if (best_match != 'overwrite') and best_match: #if the bot has an answer to the question
            answer: str = get_answer_for_question(best_match, knowledge_base)
            print(f'Bot: {answer}')
            

        else: #if the bot does not have an answer, you can enter it in and the bot remembers for next time
            if user_input != 'overwrite':
                print('Bot: I do not know the answer. Can you teach me?')
                new_answer: str = input('Type answer or "skip" to skip: ')

                if new_answer.lower() != 'skip': #or you can not enter it in 
                    knowledge_base["questions"].append({"question": user_input, "answer": new_answer})
                    save_knowledge_base('knowledge_base.json', knowledge_base)
                    print('Bot: Thank you! I learned a new response.')

def transfer(file_path: str): #function used to transfer the dialogue text file to the knowledge_base, only had to run once  
    with open(file_path, 'r', encoding="utf-8") as file:
        content = file.read()
        list = content.split('__eou__')
        new_dict = {"questions":[]}
        for i in range(0, len(list) - 1):
            if i % 2 == 0:
                new_dict["questions"].append({
                "question": list[i],
                "answer": list[i + 1]
            })
        with open('knowledge_base.json', 'w') as file:
            json.dump(new_dict, file, indent=2)
        
    

if __name__ == '__main__':
    # transfer('dialogues_text.txt')
    chat_bot()
