//
//  GPDEventsDetailViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDEventsDetailViewController.h"
#import "GPDImageFetcher.h"
#import <EventKit/EventKit.h>
#import <EventKitUI/EventKitUI.h>

@interface GPDEventAnnotation : NSObject <MKAnnotation>
@property (strong, nonatomic) id <SCBaseLocation> event;
@end

@implementation GPDEventAnnotation : NSObject
- (CLLocationCoordinate2D)coordinate
{
    CLLocationCoordinate2D coord = CLLocationCoordinate2DMake(self.event.locLatitude, self.event.locLongitude);
    return coord;
}
@end

@interface GPDEventsDetailViewController ()
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet MKMapView *mapView;
@property (strong, nonatomic) CLLocationManager *locationManager;
@end


@implementation GPDEventsDetailViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    UIImage *cachedImage = [[GPDImageFetcher sharedInstance] cachedImageForURL:self.event.imageUrl];
    if (cachedImage) {
        self.imageView.image = cachedImage;
    } else {
        [[GPDImageFetcher sharedInstance] fetchImageForURL:self.event.imageUrl
                                                     cache:YES
                                                completion:^(UIImage *image) {
                                                    self.imageView.image = image;
                                                }];
    }
    
    self.titleLabel.text = self.event.eventName;
    self.detailLabel.text = [NSString stringWithFormat:@"%@\n\n%@",
                             self.event.shortDescription,
                             self.event.longDescription];
    SCEventInstance *firstInstance = [self.event.instances firstObject];
    GPDEventAnnotation *annotation = [GPDEventAnnotation new];
    annotation.event = firstInstance;
    
    [self.mapView addAnnotation:annotation];
    [self.mapView setRegion:MKCoordinateRegionMake(annotation.coordinate, MKCoordinateSpanMake(0.1, 0.1))];
    
    self.addressLabel.text = [NSString stringWithFormat:@"%@\n%@, %@ %@",
                              firstInstance.locAddr,
                              firstInstance.locCity,
                              firstInstance.locState,
                              firstInstance.locZipcode];
    
    self.distanceLabel.text = @"";
    
    self.locationManager = [[CLLocationManager alloc] init];
    self.locationManager.delegate = self;
    if ([self.locationManager respondsToSelector:@selector(requestWhenInUseAuthorization)]) {
        [self.locationManager requestWhenInUseAuthorization];
    }
    self.locationManager.desiredAccuracy = kCLLocationAccuracyHundredMeters;
    [self.locationManager startUpdatingLocation];
}

- (IBAction)share:(id)sender {
    NSString *text = [[NSString alloc] initWithFormat:@"%@\n\n%@\n%@",
                      self.event.eventName,
                      self.event.shortDescription,
                      self.event.longDescription];
    
    UIActivityViewController *vc = [[UIActivityViewController alloc] initWithActivityItems:@[text] applicationActivities:nil];
    [self.sideMenuViewController presentViewController:vc animated:YES completion:nil];
}

- (IBAction)addToCalendar:(id)sender {
    EKEventStore *store = [[EKEventStore alloc] init];
    [store requestAccessToEntityType:EKEntityTypeEvent completion:^(BOOL granted, NSError *error) {
        if (!granted) { return; }
        
        SCEventInstance *firstInstance = [self.event.instances firstObject];
        EKEvent *event = [EKEvent eventWithEventStore:store];
        event.title = self.event.eventName;
        event.startDate = firstInstance.startDate;
        event.endDate = firstInstance.stopDate;
        [event setCalendar:[store defaultCalendarForNewEvents]];
        
        EKEventEditViewController *vc = [[EKEventEditViewController alloc] init];
        vc.event = event;
        vc.eventStore = store;
        vc.editViewDelegate = self;
        [[[UIApplication sharedApplication].delegate window].rootViewController presentViewController:vc animated:YES completion:nil];
    }];
}

- (IBAction)getDirections:(id)sender {
    SCEventInstance *location = [self.event.instances firstObject];
    if (location) {
        CLLocationCoordinate2D coordinate =
        CLLocationCoordinate2DMake(location.locLatitude, location.locLongitude);
        
        MKPlacemark* place = [[MKPlacemark alloc] initWithCoordinate:coordinate addressDictionary: nil];
        MKMapItem* destination = [[MKMapItem alloc] initWithPlacemark: place];
        destination.name = location.locAddr;
        NSDictionary* options = [[NSDictionary alloc] initWithObjectsAndKeys:
                                 MKLaunchOptionsDirectionsModeDriving,
                                 MKLaunchOptionsDirectionsModeKey, nil];
        [MKMapItem openMapsWithItems:@[destination] launchOptions: options];
    }
}

- (IBAction)call:(id)sender {
    SCEventInstance *firstInstance = [self.event.instances firstObject];
    NSString *phone = firstInstance.locPhoneNumber;
    if (phone.length) {
        NSString *strippedPhoneNumber = [[phone componentsSeparatedByCharactersInSet:[[NSCharacterSet decimalDigitCharacterSet] invertedSet]] componentsJoinedByString:@""];
        NSString *telLink = [@"tel://" stringByAppendingString:strippedPhoneNumber];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:telLink]];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"tel://8773722786"]];
    }
}

#pragma mark EKEventEditViewDelegate
- (void)eventEditViewController:(EKEventEditViewController *)controller didCompleteWithAction:(EKEventEditViewAction)action
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark CLLocationManagerDelegate

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    const double mileToMeter = 1609.f;

    [manager stopUpdatingHeading];
    
    GPDEventAnnotation *annotation = [self.mapView.annotations firstObject];
    CLLocation *location = [locations firstObject];
    
    if (!annotation || !location) {
        return;
    }
    

    CLLocation *eventLocation = [[CLLocation alloc] initWithLatitude:annotation.coordinate.latitude longitude:annotation.coordinate.longitude];

    CGFloat miles = [location distanceFromLocation:eventLocation]/mileToMeter;
    self.distanceLabel.text = [NSString stringWithFormat:@"%d mi", (int)miles];
}

@end
