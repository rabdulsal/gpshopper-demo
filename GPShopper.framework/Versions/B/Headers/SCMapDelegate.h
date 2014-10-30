//
//  SCMapDelegate.h
//  EXPproject
//
//  Created by kimberly on 6/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

/**
 Helper functions for working with MapKit data types.
 */
@interface SCMapUtil : NSObject

/**
 Filtered array containing annotations inside a region.
 
 @param as Array of id<MKAnnotation> instances.
 @param r The region which must contain the annotations.
 
 @return Array of id<MKAnnotation> instances which are contained in r.
 */
+(NSArray *)annotations: (NSArray *)as
           insideRegion: (MKCoordinateRegion)r;

/**
 @return Average of coordinates.

 @param as Array of id<MKAnnotation> instances.
  */
+(CLLocationCoordinate2D)averageCoordinateForAnnotations: (NSArray *)as;

/**
 @return The smallest region which contains all instances in as.
 
 @param as Array of id<MKAnnotation> instances. 
 */
+(MKCoordinateRegion)regionContainingAnnotations: (NSArray *)as;

/**
 @return Largest region with given center and containing region.
 
 @param c Center of output region.
 @param r Region which must contain output region.
 */
+(MKCoordinateRegion)regionWithCenter: (CLLocationCoordinate2D)c
                         insideRegion: (MKCoordinateRegion)r;

/**
 String description of CLLocationCoordinate2D suitable for logging.
 */
+(NSString *)descriptionOfCoordinate: (CLLocationCoordinate2D)c;

/**
 String description of MKCoordinateSpan suitable for logging.
 */
+(NSString *)descriptionOfSpan: (MKCoordinateSpan)s;

/**
 String description of MKCoordinateRegion suitable for logging.
 */
+(NSString *)descriptionOfRegion: (MKCoordinateRegion)r;

@end

/**
 Extension of MKAnnotation.
 */
@protocol SCMapAnnotation < MKAnnotation >

/**
 Reuse identifier for MKAnnotationView instances.
 */
-(NSString *)reuseIdentifier;

/**
 Creates a new MKAnnotationView instance.
 
 @return An autoreleased MKAnnotationView instance or nil.
 */
-(MKAnnotationView *)annotationView;

/**
 Configures an existing MKAnnotationView instance.
 */
-(void)configureView: (MKAnnotationView *)v;

/**
 If exists, called inside SCMapDelegate's implementation of
 mapView:annotationView:calloutAccessoryControlTapped:
 */
-(void)wasTapped;

-(void)wasSelectedFromAnnotationView: (MKAnnotationView *)v;

@end



/**
 Basic implementation of SCMapAnnotation.
 */
@interface SCBaseMapAnnotation : NSObject < SCMapAnnotation >

/** @name MKMapAnnotation methods */
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subtitle;
@property (nonatomic, readwrite) CLLocationCoordinate2D coordinate;

/** @name SCMapAnnotation methods */
@property (copy) NSString *reuseIdentifier;

/** @name UI customization */

/**
 Image for the 'pin' shown in MKMapView.
 */
@property (retain) UIImage *image;

/**
 Shows an arrow ('disclosure') button.
 */
@property (readwrite) BOOL showsDisclosureButton;

@property (retain) UIImage *leftAccessoryImage;

@property (retain) UIImage *rightAccessoryImage;

@end



/**
 Designed to work with id<SCMapAnnotation> instances,
 but will accept id<MKMapAnnotation> instances as well.
 
 Forwards accessory taps to id<SCMapAnnotation> instances' click method.
 */
@interface SCMapDelegate : NSObject < MKMapViewDelegate >

@property (readwrite) double dlat;
@property (readwrite) double dlon;

@end


/**
 Convenience functions.
 */
@interface MKMapView ( SCMaps )

/**
 Adds a simple annotation to the map view.  Image only, no popup.
 
 @param c Location of the annotation.
 
 @param i 'Pin' image for the annotation.
 */
-(void)addAnnotationWithCoordinate: (CLLocationCoordinate2D)c
                             image: (UIImage *)i;

/**
 Resizes map around its annotations.
 
 @param s The minimum span of the map after resizing.  Suggestion:  (0.01, 0.01)
 */
-(void)reorientWithMinSpan: (MKCoordinateSpan)s;

@end


@interface MKMapItem ( SCMaps )

+(void)openMapWithLatlon: (CLLocationCoordinate2D)l
                  street: (NSString *)s0
                    city: (NSString *)c
                   state: (NSString *)s1
                 zipcode: (NSString *)z;

+(void)openMapWithLatlon: (CLLocationCoordinate2D)l
                  street: (NSString *)s0
                    city: (NSString *)c
                   state: (NSString *)s1
                 zipcode: (NSString *)z
           launchOptions: (NSDictionary *)lo;

@end
