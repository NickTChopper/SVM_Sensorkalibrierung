#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

// Qt includes
#include <QStringList>
#include <QDir>

// other includes
#include <iostream>
#include <vector>

// OpenCv includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace cv;
using namespace cv::ml;

/*
cv::HOGDescriptor::HOGDescriptor 	( 	Size  	_winSize,
        Size  	_blockSize,
        Size  	_blockStride,
        Size  	_cellSize,
        int  	_nbins,
        int  	_derivAperture = 1,
        double  	_winSigma = -1,
        int  	_histogramNormType = HOGDescriptor::L2Hys,
        double  	_L2HysThreshold = 0.2,
        bool  	_gammaCorrection = false,
        int  	_nlevels = HOGDescriptor::DEFAULT_NLEVELS,
        bool  	_signedGradient = false
    )
 */

/*
int main(){

    int width = 350, height = 350; // TAKE THIS HARD CODING OUT!

    std::vector<String> filenames_wheels, filenames_non_wheels, filenames_test_data;

    String folder_wheels = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/labeled_data/wheels";
    String folder_non_wheels = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/labeled_data/non_wheels";
    String folder_test_data = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/test_data";

    glob(folder_wheels, filenames_wheels);
    glob(folder_non_wheels, filenames_non_wheels);
    glob(folder_test_data, filenames_test_data);

    // Setting up the label data
    int nof_training_data = filenames_wheels.size() + filenames_non_wheels.size();
    int labels_prev[nof_training_data];

    for( int i = 0; i < filenames_wheels.size(); i++ )
        labels_prev[i] = 1;

    for( int i = filenames_wheels.size(); i < nof_training_data; i++)
        labels_prev[i] = -1;

    Mat labels(nof_training_data, 1, CV_32SC1, labels_prev);

    int amount_of_pixels = width * height;
    Mat training_mat(nof_training_data, amount_of_pixels, CV_32FC1);

    int file_number = 0;

    Mat wheel_image = imread(filenames_wheels[0],0);

    Size winSize(320,320);
    Size blockSize(16,16);
    Size blockStride(16,16);
    Size cellSize(16,16);
    int nBins = 18;

    HOGDescriptor hog( winSize, blockSize, blockStride, cellSize, nBins);

    vector<float> ders;
    vector<Point> locs;

    Mat resized_wheel_image;
    resize(wheel_image, resized_wheel_image, Size(320,320));

    hog.compute(resized_wheel_image, ders, Size(320, 320), Size(0, 0), locs);



    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow( "Display window", resized_wheel_image );
    waitKey(-1);

    return 0;
}
*/

int main(){
    // HOG parameters
    Size winSize(320,320);
    Size blockSize(32,32);
    Size blockStride(16,16);
    Size cellSize(8,8);
    int nBins = 50;

    //
    /*
    HOGDescriptor hog( winSize, blockSize, blockStride, cellSize, nBins);
    vector<float> ders;
    vector<Point> locs;
    Mat tester(320, 320, CV_8UC3, Scalar(0,0,255));
    hog.compute(tester, ders, Size(320, 320), Size(0, 0), locs);
    std::cout << ders.size() << std::endl;
    */

    long nof_data = 288800;
    //long nof_data = 2*(winSize.height*winSize.width/(cellSize.height*cellSize.width))*nBins;

    // Data for visual representation
    // Reading training data (images) of both wheel-images as well as non-wheel images
    int width = 320, height = 320; // TAKE THIS HARD CODING OUT!

    std::vector<String> filenames_wheels, filenames_non_wheels, filenames_test_data;

    String folder_wheels = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/labeled_data/wheels";
    String folder_non_wheels = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/labeled_data/non_wheels";
    String folder_test_data = "/home/kursat/qt-workspace/SVM_Sensorkalibrierung/SVM_Sensorkalibrierung/test_data";

    glob(folder_wheels, filenames_wheels);
    glob(folder_non_wheels, filenames_non_wheels);
    glob(folder_test_data, filenames_test_data);

    // Setting up the label data
    int nof_training_data = filenames_wheels.size() + filenames_non_wheels.size();
    int labels_prev[nof_training_data];

    for( int i = 0; i < filenames_wheels.size(); i++ )
        labels_prev[i] = 1;

    for( int i = filenames_wheels.size(); i < nof_training_data; i++)
        labels_prev[i] = -1;

    Mat labels(nof_training_data, 1, CV_32SC1, labels_prev);

    int amount_of_pixels = width * height;
    Mat training_mat(nof_training_data, nof_data, CV_32FC1);

    int file_number = 0;

    // Craeting the training data by saving one image per row (reshaping: whole image data is
    // stored in a single row by placing subseauently the rows of the image one after the other in a single row)

    // 1. Store the training data for positive samples (wheel)
    for(unsigned int i = 0; i < filenames_wheels.size(); i++){
        Mat wheel_image = imread(filenames_wheels[i],0);
        resize(wheel_image,wheel_image, Size(width,height));

        if(!wheel_image.data){
            std::cout << "Problem loading image: " << filenames_wheels[i] << std::endl;
            std::cout << "Program is terminated! " << std::endl;
            return 0;
        }else{
            if( wheel_image.rows > height ){
                std::cout << i << "-th wheel image: " << std::endl;
                std::cout << "The amount of rows in this image exceeds the input width! An error will occurr." << std::endl;
            }
            if( wheel_image.cols > width ){
                std::cout << i << "-th wheel image: " << std::endl;
                std::cout << "The amount of cols in this image exceeds the input height! An error will occurr." << std::endl;
            }

            HOGDescriptor hog( winSize, blockSize, blockStride, cellSize, nBins);

            vector<float> ders;
            vector<Point> locs;
            hog.compute(wheel_image, ders, Size(320, 320), Size(0, 0), locs);

            int ii = 0; // Current column in training_mat
            for (int i = 0; i < ders.size(); i++) {
                training_mat.at<float>(file_number,ii++) = ders.at(i);
            }

            // Set up the labels for the classes, +1 for wheel - not done here but could have been done here to avoid it later...
            file_number++;
        }

     }

    // 2. Store the training data for negative samples (non-wheel)
    // ERROR: Take the -2 out of the for loop header. I put it inside since the image sizes aren't correct yet and error is outputted cuz of wrong element access
    for(unsigned int i = 0; i < filenames_non_wheels.size()-2; i++){
        Mat non_wheel_image = imread(filenames_non_wheels[i],0);
        resize(non_wheel_image,non_wheel_image, Size(width,height));


        if(!non_wheel_image.data){
            std::cout << "Problem loading image: " << filenames_non_wheels[i] << std::endl;
            std::cout << "Program is terminated!" << std::endl;
            return 0;
        }else{
            if( non_wheel_image.rows > height ){
                std::cout << i << "-th wheel image: " << std::endl;
                std::cout << "The amount of rows in this image exceeds the input width! An error will occurr." << std::endl;
            }
            if( non_wheel_image.cols > width ){
                std::cout << i << "-th wheel image: " << std::endl;
                std::cout << "The amount of cols in this image exceeds the input height! An error will occurr." << std::endl;
            }

            HOGDescriptor hog( winSize, blockSize, blockStride, cellSize, nBins);

            vector<float> ders;
            vector<Point> locs;
            hog.compute(non_wheel_image, ders, Size(320, 320), Size(0, 0), locs);

            int ii = 0; // Current column in training_mat
            for (int i = 0; i < ders.size(); i++) {
                training_mat.at<float>(file_number,ii++) = ders.at(i);
            }

            // Set up the labels for the classes, -1 for non-wheel - not done here but could have been done here to avoid it later...
            file_number++;
        }
     }

    // Set up the labels for the classes: +1 for wheels, -1 for non-wheels. ERROR:Das müsste falsch sein??
    //labels.rowRange( 0, filenames_wheels.size()).setTo(1);  // Class 1
    //labels.rowRange( filenames_wheels.size(), filenames_wheels.size() + filenames_non_wheels.size()).setTo(-1);


    //------------------------ 2. Set up the support vector machines parameters --------------------
    std::cout << "Starting training process" << std::endl;
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setC(0.1);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, (int)1e7, 1e-6));
    std::cout << "Training..." << std::endl;
    svm->train(training_mat, ROW_SAMPLE, labels);
    std::cout << "Finished training process" << std::endl;


    //------------------------ 3. Predict -------------------- OpenCV current version (old)

    Mat sample_mat(1, nof_data, CV_32FC1);

    for( int j = 0; j<filenames_test_data.size(); j++){

        int sample_file_number = j;
        Mat sample_mat_file = imread(filenames_test_data[sample_file_number],0);
        resize(sample_mat_file,sample_mat_file,Size(width,height));

        // Here you should also check whether file size is ok...

        // Put the sample file into a single line

        HOGDescriptor hog( winSize, blockSize, blockStride, cellSize, nBins);

        vector<float> ders;
        vector<Point> locs;
        hog.compute(sample_mat_file, ders, Size(320, 320), Size(0, 0), locs);

        int ii = 0; // Current column in training_mat
        for (int i = 0; i < ders.size(); i++) {
            sample_mat.at<float>(0,ii++) = ders.at(i);
        }


        std::cout << "filename: " << filenames_test_data[sample_file_number] << std::endl;
        std::cout << svm->predict(sample_mat) << std::endl;

        namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
        imshow( "Display window", sample_mat_file );

        waitKey(-1);


    }

    //SVM.predict(sample_mat);
    //std::cout << SVM.predict( sample_mat ) << std::endl;
    //float response = SVM.predict(sample_mat);
    //std::cout << response << std::endl;


    //------------------------ 2. Set up the support vector machines parameters -------------------- OpenCV new version (not installed)
/*
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setC(0.1);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, (int)1e7, 1e-6));
    //svm->train(training_mat, ROW_SAMPLE, labels);
    std::cout << "Finished training process" << std::endl;
*/

    std::cout << "PASSED" << std::endl;
    return 0;
}

