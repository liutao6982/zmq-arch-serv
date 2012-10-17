#ifndef __GRID_FUNC_HPP__
#define __GRID_FUNC_HPP__


#include <iostream>
#include <math.h>

#include <assert.h>


namespace CCTool{
namespace GridFunc{


	const double PI = 3.141592653589793;

	static int power(int m)
	{
		assert( m > 0 );
		return 1 << m;
	}

	static double toRadioans(double angdeg)
	{
		return angdeg / 180.0 * PI;
	}

	static double checkLongitude(double longitude) 
	{
		while (longitude < -180 || longitude > 180) 
		{
			if (longitude < 0) {
				longitude += 360;
			} else {
				longitude -= 360;
			}
		}
		return longitude;
	}

	static double checkLatitude(double latitude) 
	{
		while (latitude < -90 || latitude > 90) {
			if (latitude < 0) {
				latitude += 180;
			} else {
				latitude -= 180;
			}
		}
		return latitude;
	}

	static int getTileNumberX(int zoom, double longitude)
	{
		longitude = checkLongitude(longitude);
		double pixelX = ((longitude + 180) / 360) * 256 * power(zoom);
		int tileX = floor(pixelX / 256);
		return tileX;
	}

	static int getTileNumberY(int zoom, double latitude)
	{
		latitude = checkLatitude(latitude);
		double sinLatitude = sin(latitude * PI / 180);
		double pixelY =(0.5 - log((1 + sinLatitude) / (1 - sinLatitude)) / (4 * PI)) * 256 * power(zoom);
		int tileY = floor(pixelY / 256);
		return tileY;
	}

	static double getLongitudeFromTile(int zoom, double x) {
		return x / power(zoom) * 360.0 - 180.0;
	}

	static double getLatitudeFromTile(int zoom, double y){
		int sign = y < 0 ? -1 : 1;
		double result = atan(sign*sinh(PI * (1 - 2 * y /
			power(zoom)))) * 180 / PI;
		return result;
	}

	static double getDistance(double lat1, double lon1, double
		lat2, double lon2){
			double R = 6371; // km
			double dLat = toRadioans(lat2-lat1);
			double dLon = toRadioans(lon2-lon1);
			double a = sin(dLat/2) * sin(dLat/2) +
				cos(toRadioans(lat1)) *
				cos(toRadioans(lat2)) *
				sin(dLon/2) * sin(dLon/2);
			double c = 2 * atan2(sqrt(a), sqrt(1-a));
			return R * c * 1000;
	}

}}

#endif