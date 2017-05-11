#region Using

using System;
using System.IO;

using NAudio.Wave;

#endregion


namespace SoundWave.MediaPlayer
{
    public class SoundPlayer
    {
        #region Public Funcitons

        /// <summary>
        /// construction
        /// </summary>
        public SoundPlayer()
        {
        }


        /// <summary>
        /// plays a .wav file
        /// </summary>
        public void PlayWav( String aWaveFile )
        {
            if (aWaveFile.Length == 0)
            {
                return;
            }

            // read in the wave file
            myWaveFileReader = new WaveFileReader( aWaveFile );
            if( myWaveFileReader.Length == 0 )  
            {
                return;
            }

            // use a WaveOutEvent to play the file
            mySoundOutput = new WaveOutEvent();
            mySoundOutput.Init( myWaveFileReader );
            mySoundOutput.Play();
        }


        /// <summary>
        /// stops playback of the current .wav
        /// </summary>
        public void Stop()
        {
            if( mySoundOutput != null )
            {
                // clean up the file reader
                myWaveFileReader.Dispose();
                myWaveFileReader = null;

                // clear up the output device
                mySoundOutput.Stop();
                mySoundOutput.Dispose();
                mySoundOutput = null;
            }
        }

        #endregion


        #region Private Member Variables

        private WaveOutEvent    mySoundOutput       = null;
        private WaveFileReader  myWaveFileReader    = null;

        #endregion
    }
}
