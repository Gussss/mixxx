/***************************************************************************
                          readerextractwave.h  -  description
                             -------------------
    begin                : Thu Feb 6 2003
    copyright            : (C) 2003 by Tue & Ken Haste Andersen
    email                : haste@diku.dk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef READEREXTRACTWAVE_H
#define READEREXTRACTWAVE_H

#include "readerextract.h"
#include "defs.h"
#include "monitor.h"
#include "soundsource.h"
#include <qevent.h>

//#include <qfile.h>

class SignalVertexBuffer;
class ReaderExtractFFT;
class ReaderExtractHFC;
class ReaderExtractBeat;
class Reader;

#define EXTRACT

/**
  * This is the main ReaderExtract class, taking care of buffering the incoming wave data from
  * the SoundSource objects, and subsequently calls other ReaderExtract objects.
  *
  *@author Tue Haste Andersen
  */

class ReaderExtractWave : ReaderExtract {
public: 
    ReaderExtractWave(Reader *pReader);
    ~ReaderExtractWave();
    void addVisual(GUIChannel *_guichannel);
    void reset();
    void *getBasePtr();
    int getRate();
    int getChannels();
    int getBufferSize();
    ReaderExtractBeat *getExtractBeat();
    void *processChunk(const int, const int, const int, bool);
    void setSoundSource(SoundSource *_file);
    /** Read a new chunk into the readbuffer: */
    void getchunk(CSAMPLE rate);
    /** Seek to a new play position. Returns positon actually seeked to */
    long int seek(long int new_playpos);
    /** The first read sample in the file, currently in read_buffer. This should only be
      * accessed while holding the enginelock from the reader class. */
    long int filepos_start;
    /** The last read sample in the file, currently in read_buffer. This should only be
      * accessed while holding the enginelock from the reader class. */
    long int filepos_end;
private:
    /** Pointer to Reader class */
    Reader *m_pReader;
    /** Temporary buffer for the raw samples */
    SAMPLE *temp;
    /** Buffer start and end position */
    int bufferpos_start, bufferpos_end;
    /** Pointer to GUIChannel associated with this buffer */
    GUIChannel *guichannel;
    /** Pointer to the sound source */
    SoundSource *file;
    int stepSize;
    int windowPerChunk;
    int windowNo;
    /** The buffer where the samples are read into */
    CSAMPLE *read_buffer;
    /** Pointer to FFT extractor */
    ReaderExtractFFT *readerfft;
    ReaderExtractHFC *readerhfc;
    ReaderExtractBeat *readerbeat;

//    QFile textout;
};

#endif
