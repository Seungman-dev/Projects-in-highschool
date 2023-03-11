# -*- coding: utf-8 -*-

from bs4 import BeautifulSoup
import konlpy #자연어처리
import nltk #자연어처리
import pandas as pd #정적으로 대용량의 데이터들을 처리하는데 매우 편리한 도구
import re #정규표현식 사용하기 위해

# 파일 관리를 위한 모듈 추가
import os #Operating System의 약자, 운영체제에서 제공되는 여러 기능을 수행할 수 있게 해줌
import shutil

#from regex import P #파일 관리

file_path = os.path.dirname(os.path.realpath(__file__))  # 폴더 절대경로
file_path.replace('\\', '\\\\')

article_aclass = ['pol', 'eco', 'nav', 'lif', 'wor', 'sci']



#자연어 처리 함수
def clean_korean_documents(document):
    #텍스트 정제 (HTML 태그 제거)
    document = BeautifulSoup(document, 'html.parser').text 

    #텍스트 정제 (특수기호 제거)
    document = re.sub(r'[^ ㄱ-ㅣ가-힣]', '', document) #특수기호 제거, 정규 표현식

    #텍스트 정제 (형태소 분석)
    okt = konlpy.tag.Okt()
    clean_words = []
    for word in okt.pos(document, stem=True): #어간 추출
        if word[1] in ['Noun', 'Verb', 'Adjective']: #명사, 동사, 형용사
            clean_words.append(word[0])
    document = ' '.join(clean_words)

    #텍스트 정제 (불용어 제거)
    df = pd.read_csv('https://raw.githubusercontent.com/cranberryai/todak_todak_python/master/machine_learning_text/clean_korean_documents/korean_stopwords.txt', header=None)
    df[0] = df[0].apply(lambda x: x.strip())
    stopwords = df[0].to_numpy()
    nltk.download('punkt')
    clean_words = [] 
    for word in nltk.tokenize.word_tokenize(document): 
        if word not in stopwords: #불용어 제거
            clean_words.append(word)
    document = ' '.join(clean_words)  

    return document


if os.path.exists(file_path + '\\자연어 처리 로그'):
    shutil.rmtree(file_path + '\\자연어 처리 로그') 
os.mkdir(file_path + '\\자연어 처리 로그')

for i in article_aclass:
    os.mkdir(file_path + '\\자연어 처리 로그\\'+i)
    


for i in article_aclass:
    for j in range(1, len(os.listdir(file_path + '\\뉴스 크롤링 로그\\' + i)) + 1):
        with open(f"{file_path}\\뉴스 크롤링 로그\\{str(i)}\\크롤링 로그 {j}번째.txt", "r", encoding="utf8") as file: #절대경로에 있는 파일 읽기
            document = clean_korean_documents(file.read()) #파일에서 읽은 문서를 자연어처리한 수 document변수에 저장
        with open(f"{file_path}\\자연어 처리 로그\\{str(i)}\\자연어 처리 로그 {j}번째.txt", "w", encoding="utf8") as file: #절대경로에 파일 만들기
            file.write(document)

print("자연어 처리 완료")

