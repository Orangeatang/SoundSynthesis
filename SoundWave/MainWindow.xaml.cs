#region Using

using System;
using System.IO;
using System.Timers;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Forms;
using System.Windows.Threading;

using SoundWave.MediaPlayer;

#endregion


namespace SoundWave
{
    #region Resolve Ambiguities 

    using Timer         = System.Timers.Timer;
    using Application   = System.Windows.Application;

    #endregion


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Public Functions

        public MainWindow()
        {
        }

        #endregion


        #region Application Events

        /// <summary>
        /// Triggered when the application is first loaded, sets up C++ rendering & engine update
        /// </summary>
        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            if( !SoundSynthesisInterface.Instance.InitialiseEngine(myDXControl.Handle, (int)myDXControl.Width, (int)myDXControl.Height) )
            {
                return;
            }

            // create a timer to tick the engine
            myTimer = new Timer(33);
            myTimer.Elapsed += OnUpdateEngine;
            myTimer.AutoReset = true;
            myTimer.Enabled = true;
        }


        /// <summary>
        /// handles cleanup of the application
        /// </summary>
        private void OnExit( object aSender, EventArgs someArges )
        {
            Application.Current.Shutdown( 0 );
        }


        /// <summary>
        /// triggered when the user clicks on the input file selection button
        /// </summary>
        private void OnInputFileClicked(object aSender, RoutedEventArgs someArgs)
        {
//             OpenFileDialog fileDialog = new OpenFileDialog();
//             fileDialog.Filter = "WAV files (*.wav)|*.wav";
//             fileDialog.RestoreDirectory = true;
//             if (fileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
//             {
//                 myInputFileName = fileDialog.FileName;
//                 myInputFileText.Text = Path.GetFileName(myInputFileName);
//                 myOutputFileName = Path.GetDirectoryName(myInputFileName) + "\\" + Path.GetFileNameWithoutExtension(myInputFileName) + " Output.wav";
// 
//                 myOutputFileText.Text = Path.GetFileName(myOutputFileName);
// 
//                 EnableUI();
//             }
        }


        /// <summary>
        /// triggers quantization conversion of input audio file
        /// </summary>
        private void OnBeginQuantization(object aSender, RoutedEventArgs someArgs)
        {
//             if (myInputFileName.Length == 0)
//             {
//                 return;
//             }
// 
//             if (myQuantizationBits.SelectedIndex == -1)
//             {
//                 return;
//             }
// 
//             DisableUI();
// 
//             // stop any output
//             mySoundPlayer.Stop();
// 
//             SetStatusBarText("Processing Quantization...");
//             SoundSynthesisInterface.Instance.QuantizeAudioFile(myInputFileName, myOutputFileName, (int)myQuantizationBits.SelectedItem);
//             SetStatusBarText("Quantization Complete!");
// 
//             EnableUI();
        }


        /// <summary>
        /// Changes the value of the pitch shift label
        /// </summary>
        private void OnPitchShiftValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
//             if (myPitchShiftLabel != null)
//             {
//                 myPitchShiftLabel.Content = Math.Round(myPitchShiftFactor.Value, 3);
//             }
        }


        private void OnBeginPitchShift(object aSender, RoutedEventArgs someArgs)
        {
//             if (myInputFileName.Length == 0)
//             {
//                 return;
//             }
// 
//             DisableUI();
// 
//             mySoundPlayer.Stop();
// 
//             SetStatusBarText("Procesing Pitch Shift...");
//             SoundSynthesisInterface.Instance.PitchShiftAudioFile(myInputFileName, myOutputFileName, Math.Round(myPitchShiftFactor.Value, 3));
//             SetStatusBarText("Pitch Shift Complete!");
// 
//             EnableUI();
        }


        /// <summary>
        /// triggers playback of generated audio file
        /// </summary>
        private void OnPlayOutput(object aSender, RoutedEventArgs someArgs)
        {
//             mySoundPlayer.Stop();
//             mySoundPlayer.PlayWav(myOutputFileName);
        }


        /// <summary>
        /// triggers playback of the input audio file
        /// </summary>
        private void OnPlayInput(object aSender, RoutedEventArgs someArgs)
        {
//             mySoundPlayer.Stop();
//             mySoundPlayer.PlayWav(myInputFileName);
        }


        /// <summary>
        /// stops playback of generated audio file
        /// </summary>
        private void OnStopOutput(object aSender, RoutedEventArgs someArgs)
        {
            //mySoundPlayer.Stop();
        }


        private void OnUpdateEngine(object aSender, ElapsedEventArgs someArgs)
        {
            SoundSynthesisInterface.Instance.Update();
        }

        #endregion


        #region Private Member Functions

        /// <summary>
        /// Initializes the Quantization UI
        /// </summary>
        private void SetupQuantization()
        {
//             for( int i = 1; i < 16; ++i )
//             {
//                 myQuantizationBits.Items.Add( i );
//             }
// 
//             myQuantizationBits.SelectedIndex    = 0;
//             myBeginQuantizationButton.IsEnabled = false;
        }

        /// <summary>
        /// Enables parts of the UI previously disabled (due to lack of input)
        /// </summary>
        private void EnableUI()
        {
//             myBeginQuantizationButton.IsEnabled = true;
//             myBeginPitchShiftButton.IsEnabled = true;
        }

        
        /// <summary>
        /// Disables user interface elements
        /// </summary>
        private void DisableUI()
        {
//             myBeginQuantizationButton.IsEnabled = false;
//             myBeginPitchShiftButton.IsEnabled = false;
        }


        /// <summary>
        /// Updates the status bar text
        /// </summary>
        private void SetStatusBarText( string someText )
        {
            //m_statusBarText.Text = someText;

            // force the UI to refresh
            DispatcherFrame frame = new DispatcherFrame();
            Dispatcher.CurrentDispatcher.BeginInvoke(DispatcherPriority.Render, new DispatcherOperationCallback(delegate (object parameter)
            {
                frame.Continue = false;
                return null;

            }), null);

            Dispatcher.PushFrame(frame);
        }

        #endregion


        #region Private Member Variables

        String      myInputFileName     = "";
        String      myOutputFileName    = "";
        Timer       myTimer             = null;

        SoundPlayer mySoundPlayer;

        #endregion
    }
}
