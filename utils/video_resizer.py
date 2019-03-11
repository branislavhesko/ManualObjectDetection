import argparse

import cv2
import numpy as np
from scipy.misc import imresize


def resize_video(filename, size, output_filename=None):
    size = tuple([int(s) for s in size])
    video = cv2.VideoCapture(filename)
    print(video.get(cv2.CAP_PROP_FOURCC))
    output_video = cv2.VideoWriter(output_filename, apiPreference=int(cv2.CAP_FFMPEG), fps=int(video.get(cv2.CAP_PROP_FPS)), fourcc=cv2.VideoWriter_fourcc(*"PIM1"), frameSize=size[-1::-1])
    if not video.isOpened():
        raise IOError("Video could not be loaded")

    while video.isOpened():
        ret, frame = video.read()

        if ret:
            output_frame = imresize(frame, (*size, 3))
            output_video.write(output_frame)
        else:
            break

    video.release()
    output_video.release()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='As a standalone application, this script resizes the  passed video.')
    parser.add_argument("-filename", action="store", dest="input_file", const="UNKNOWN",
                        help="Video file to be processed", nargs="?")
    parser.add_argument("-size", dest="size", default=(720, 1280), 
                        action="store", help="New size of the video!", nargs="+")
    parser.add_argument("-output", action="store", dest="output_file", default=None, help="Name of the output file")
    args = parser.parse_args()
    resize_video(args.input_file, args.size, args.output_file)
