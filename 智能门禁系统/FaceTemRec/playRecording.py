#!/usr/bin/python
#coding:utf-8
"""
播放语音
"""
# def playMusic(musicPath):
#     from playsound import playsound
#     playsound(musicPath)
#
#

import time
from threading import Thread

import pygame


# def PlayRecording(musicPath):
# #     pygame.mixer.init()
# #     track = pygame.mixer.music.load(musicPath)
# #     if musicPath == 'music/faceRecFail.mp3':
# #         print('test')
# #         pygame.mixer.music.play()
# #         time.sleep(3)
# #         pygame.mixer.music.stop()
# #     else:
# #         pygame.mixer.music.play()
# #         time.sleep(2)
# #         pygame.mixer.music.stop()
# #
# #
# # if __name__ == '__main__':
# #     Thread(PlayRecording("music/success.mp3"))

def PlayRecording(musicPath):
    pygame.mixer.init()
    track = pygame.mixer.music.load(musicPath)


if __name__ == '__main__':
    PlayRecording("music/networkAbnormal.mp3")
    pygame.mixer.music.play()
    time.sleep(3)
    pygame.mixer.music.stop()
