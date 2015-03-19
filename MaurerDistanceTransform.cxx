#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"
#include "MaurerDistanceTransformCLP.h"



/* Creates the MaurerDistanceTransform filter and the output image with the input type. */
int MaurerDistanceTransform( std::string inputFileName , std::string outputFileName )
{
  typedef unsigned int InputComponentType ;
  typedef int OutputComponentType ;
  typedef itk::Image< InputComponentType , 3 > InputImageType ;
  typedef itk::Image< OutputComponentType , 3 > OutputImageType ;
  typedef itk::SignedMaurerDistanceMapImageFilter < InputImageType , OutputImageType > FilterType ;
  FilterType::Pointer MaurerDistanceMapImageFilter = FilterType::New() ;
  InputImageType::Pointer image = InputImageType::New() ;
  typedef itk::ImageFileReader< InputImageType > ReaderType ;
  ReaderType::Pointer reader = ReaderType::New() ;
  reader->SetFileName( inputFileName.c_str() ) ;
  try
  {
    reader->Update() ;
  }
  catch(...)
  {
    std::cerr << "Image could not be read." << std::endl ;
    return EXIT_FAILURE ;
  }
  MaurerDistanceMapImageFilter->SetInput( image ) ;
  MaurerDistanceMapImageFilter->Update();
  typedef itk::ImageFileWriter< OutputImageType > WriterType ;
  WriterType::Pointer writer = WriterType::New() ;
  writer->SetInput( MaurerDistanceMapImageFilter->GetOutput() ) ;
  writer->SetFileName( outputFileName ) ;
  writer->Update() ;
  return EXIT_SUCCESS ;
}



int main(int argc, char * argv[])
{
    PARSE_ARGS;
    return MaurerDistanceTransform( input , output  ) ;

}

