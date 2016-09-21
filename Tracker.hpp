#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/** The class for tracking object
***/
class TrackingObj {
 public:
  /* Constructor */
  TrackingObj(unsigned int objID, Mat objAppearance, Rect bBox)
              : age(1), vel(0, 0), state(5, 1, CV_32F), KF(5, 3, 0) {
    ID = objID;
    appearance = objAppearance;

    /* convert rectangle to position and size */
    pos = make_pair(bBox.x + bBox.width / 2.0, bBox.y + bBox.height / 2.0);
    size = float(bBox.width * bBox.height);
  }

  /* Get the age of object */
  unsigned int getAge();

  /* Get the ID of the object */
  unsigned int getID();

  /* Increase the age of an object */
  void incAge();

  /* Print object information */
  void showInfo();

  /* Convert attributes to a vector of state in Mat format*/
  void attr2State();

  /* Convert state to attributes */
  void state2Attr();

  /* Compare attributes with another trackingObj */
  bool operator==(const TrackingObj& other);

  /* Show current state of Kalman filter */
  void showState();


  /* Initialize Kalman filter for a tracking object */
  void initKalmanFilter();

  /* Predict and update Kalman filter */
  void refreshKalmanFilter();

 private:
  unsigned int ID;
  unsigned int age;  // object's existing time
  Mat appearance;  // image of detected object
  pair<float, float> pos;  // center of detected object
  pair<float, float> vel;  // velocity of detected object
  float size;  // size of detected object
  Mat state;  // state of Kalman Filter
  KalmanFilter KF;  // Kalman Filter object
};

#endif  // TRACKER_HPP
