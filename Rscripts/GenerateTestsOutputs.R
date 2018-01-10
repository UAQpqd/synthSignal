

PlotCSVWithTitleAndLabels <- function(csvFilename, plotTitle, xLabel, yLabel)
{
    df = read.csv(csvFilename)
    plot(df$time, df$amplitude, type = 'l',
    main = plotTitle, xlab = xLabel, ylab = yLabel)
    grid()
}

SignalTest_SignalWithOneWaveform_CheckWaveformIsGenerated <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckWaveformIsGenerated.csv',
    'CheckWaveformIsGenerated',
    'Time (s)',
    'Amplitude (V)')
}

SignalTest_SignalWithWhiteNoise_CheckWhiteNoiseMeanIsZero <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckWhiteNoiseMeanIsZero.csv',
    'CheckWhiteNoiseMeanIsZero',
    'Time (s)',
    'Amplitude (V)')
}

SignalTest_SignalWithWhiteNoise_CheckFrequencyChanging <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckFrequencyChanging.csv',
    'CheckFrequencyChanging',
    'Time (s)',
    'Amplitude (V)')
}
SignalTest_SignalWithHarmonics_Check3rdHarmonicIsPresent <- function()
{
    PlotCSVWithTitleAndLabels(
    'Check3rdHarmonicIsPresent.csv',
    'Check3rdHarmonicIsPresent',
    'Time (s)',
    'Amplitude (V)')
}
SignalTest_SignalWithHarmonics_CheckHarmonicsArePresent <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckHarmonicsArePresent.csv',
    'CheckHarmonicsArePresent',
    'Time (s)',
    'Amplitude (V)')
}

SignalTest_SignalWithOneWaveformWithoutInterpolation_CheckSag <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckSag.csv',
    'CheckSag',
    'Time (s)',
    'Amplitude (V)')
}
SignalTest_SignalWithOneWaveformWithoutInterpolation_CheckSwell <- function()
{
    PlotCSVWithTitleAndLabels(
    'CheckSwell.csv',
    'CheckSwell',
    'Time (s)',
    'Amplitude (V)')
}
SignalTest_SignalWithOneWaveform_CheckWaveformIsGenerated()
SignalTest_SignalWithWhiteNoise_CheckWhiteNoiseMeanIsZero()
SignalTest_SignalWithWhiteNoise_CheckFrequencyChanging()
SignalTest_SignalWithHarmonics_Check3rdHarmonicIsPresent()
SignalTest_SignalWithHarmonics_CheckHarmonicsArePresent()
SignalTest_SignalWithOneWaveformWithoutInterpolation_CheckSag()
SignalTest_SignalWithOneWaveformWithoutInterpolation_CheckSwell()
shell.exec('Rplots.pdf')
