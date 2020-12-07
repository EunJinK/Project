import time

import cv2
import numpy as np
from os import makedirs
from os import listdir
from os.path import isdir, isfile, join

face_dirs = 'faces/'
# 얼굴 인식용 haar/cascade 로딩
face_classifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

num = 0
record = False

def face_extractor(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_classifier.detectMultiScale(gray, 1.3, 5)
    # 얼굴이 없으면 패스!
    if faces is ():
        return None
    # 얼굴이 있으면 얼굴 부위만 이미지로 만들고
    for (x, y, w, h) in faces:
        cropped_face = img[y:y + h, x:x + w]
    # 리턴!
    return cropped_face

def video_pictures(name):
    if not isdir(face_dirs + name):
        makedirs(face_dirs + name)
    cap_new = cv2.VideoCapture('faces/video/new.avi')
    count = 0
    while True:
        ret, frame2 = cap_new.read()
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        cv2.imshow('Face Cropper', frame)
        if face_extractor(frame2) is not None:
            count += 1
            face = cv2.resize(face_extractor(frame2), (200, 200))
            face = cv2.cvtColor(face, cv2.COLOR_BGR2GRAY)

            file_name_path = face_dirs + name + '/user' + str(count) + '.jpg'
            cv2.imwrite(file_name_path, face)

            cv2.putText(face, str(count), (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 2)
            cv2.imshow('Face', face)
        else:
            print("Face not Found")
            pass

        if cv2.waitKey(1) == 13 or count == 100:
            break
    #cap_new.release()
    print('Colleting Samples Complete!!!')


# 얼굴만 저장하는 함수
def take_pictures(name):
    if not isdir(face_dirs + name):
        makedirs(face_dirs + name)
    count = 0
    while True:
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        cv2.imshow('Face Cropper', frame)
        if face_extractor(frame) is not None:
            count += 1
            face = cv2.resize(face_extractor(frame), (200, 200))
            face = cv2.cvtColor(face, cv2.COLOR_BGR2GRAY)

            file_name_path = face_dirs + name + '/user' + str(count) + '.jpg'
            cv2.imwrite(file_name_path, face)

            cv2.putText(face, str(count), (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 2)
            cv2.imshow('Face', face)
        else:
            print("Face not Found")
            pass

        if cv2.waitKey(1) == 13 or count == 100:
            break
    #cap.release()
    print('Colleting Samples Complete!!!')


# 사용자 얼굴 학습
def train(name):
    data_path = 'faces/' + name + '/'
    face_pics = [f for f in listdir(data_path) if isfile(join(data_path, f))]

    Training_Data, Labels = [], []

    for i, files in enumerate(face_pics):
        image_path = data_path + face_pics[i]
        images = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
        if images is None:
            continue
        Training_Data.append(np.asarray(images, dtype=np.uint8)) #배열종류바꾸는 함수
        Labels.append(i)
    if len(Labels) == 0:
        print("There is no data to train.")
        return None
    Labels = np.asarray(Labels, dtype=np.int32)
    model = cv2.face.LBPHFaceRecognizer_create()
    model.train(np.asarray(Training_Data), np.asarray(Labels))
    print(name + " : Model Training Complete!!!!!")

    return model

def trains():
    data_path = 'faces/'
    model_dirs = [f for f in listdir(data_path) if isdir(join(data_path, f))]

    models = {}
    for model in model_dirs:
        print('model :' + model)
        # 학습 시작
        result = train(model)
        if result is None:
            continue
        print('model2 :' + model)
        models[model] = result

    return models


# 얼굴 검출
def face_detector(img, size=0.5):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_classifier.detectMultiScale(gray, 1.3, 5)
    if faces is ():
        return img, []
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 255), 2)
        roi = img[y:y + h, x:x + w]
        roi = cv2.resize(roi, (200, 200))
    return img, roi  # 검출된 좌표에 사각 박스 그리고(img), 검출된 부위를 잘라(roi) 전달
##############################################################################################
cap = cv2.VideoCapture(0)
fourcc = cv2.VideoWriter_fourcc(*'DIVX')

while True:
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    cv2.putText(frame,"Hello", (250, 450), cv2.FONT_HERSHEY_COMPLEX, 1, (0,0,0), 2)
    cv2.imshow('Face Cropper', frame)
    if cv2.waitKey(1) == 27:
        print("esc")
        take_pictures(str(num))
        models = trains()
        print("Train OK!")
        num+=1
    if cv2.waitKey(1) == 48:
        print("0")
        video_pictures(str(num))
        cap.release()
        models = trains()
        print("Train OK!")
        num += 1
        cap = cv2.VideoCapture(0)
    if cv2.waitKey(1) == 32:
        print("space")
        while True:
            # 카메라로 부터 사진 한장 읽기
            ret, frame = cap.read()
            frame = cv2.flip(frame, 1)
            image, face = face_detector(frame)
            try:
                min_score = 999
                min_score_name = ""

                face = cv2.cvtColor(face, cv2.COLOR_BGR2GRAY)

                for key, model in models.items():
                    result = model.predict(face)
                    if min_score > result[1]:
                        min_score = result[1]
                        min_score_name = key

                if min_score < 500:
                    confidence = int(100 * (1 - (min_score) / 300))
                    display_string = str(confidence) + '% Confidence it is ' + min_score_name
                cv2.putText(image, display_string, (100, 120), cv2.FONT_HERSHEY_COMPLEX, 1, (250, 120, 250), 2)

                if confidence > 80:
                    cv2.putText(image, "Unlocked : " + min_score_name, (250, 450), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0),
                                2)
                    cv2.imshow('Face Cropper', image)
                elif confidence <81:
                    print("not user")
                    fourcc = cv2.VideoWriter_fourcc(*'DIVX')
                    count = 0
                    print("----녹화 시작----")
                    if record == False:
                        while True:
                            ret, frame = cap.read()
                            frame = cv2.flip(frame, 1)
                            cv2.imshow('Face Cropper', frame)
                            cv2.putText(frame, "Waring!!", (250, 450), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 250), 2)
                            if record == False:
                                record = True
                                video = cv2.VideoWriter("faces/video/new.avi", fourcc, 20.0,(frame.shape[1], frame.shape[0]))
                            elif record == True:
                                video.write(frame)
                                print("   녹화 중")
                                count += 1

                            if count == 200 or cv2.waitKey(1) == 23:
                                record = False
                                video.release()
                                print("----녹화종료----")
                                time.sleep(5)
                                break
                    else:
                        pass
                    break
            except:
                print("no face")
                #cv2.putText(image, "Face Not Found", (250, 450), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 0, 0), 2)
                cv2.imshow('Face Cropper', image)
                pass
            if cv2.waitKey(1) == 13:
                break
    if cv2.waitKey(1) == 13:
        break
cap.release()
cv2.destroyAllWindows()