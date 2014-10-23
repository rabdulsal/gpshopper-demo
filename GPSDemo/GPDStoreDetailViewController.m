//
//  GPDStoreDetailViewController.m
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDStoreDetailViewController.h"



@interface GPDStoreDetailViewController ()
@property (weak, nonatomic) IBOutlet MKMapView *mapView;
@property (weak, nonatomic) IBOutlet UILabel *storeAddressLabel;

@end

@implementation GPDStoreAnnotation

- (CLLocationCoordinate2D)coordinate
{
    return CLLocationCoordinate2DMake(self.store.lat, self.store.lng);
}

- (NSString *)title
{
    return self.store.storeName;
}

- (NSString *)subtitle
{
    return self.store.streetAddress;
}

@end


@implementation GPDStoreDetailViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = self.store.storeSubname;
    
    self.storeAddressLabel.text = [NSString stringWithFormat:@"%@\n%@, %@ %@",
                                   self.store.streetAddress,
                                   self.store.city, self.store.state,
                                   self.store.zipcode];
    
    
    CLLocationCoordinate2D center = CLLocationCoordinate2DMake(self.store.lat, self.store.lng);
    MKCoordinateRegion region = MKCoordinateRegionMake(center, MKCoordinateSpanMake(0.05, 0.05));
    [self.mapView setRegion:region];
    
    
    GPDStoreAnnotation *annotation = [GPDStoreAnnotation new];
    annotation.store = self.store;
    [self.mapView addAnnotation:annotation];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    SCWebTrackingEvent *te = [SCWebTrackingEvent sectionTrackingEventWithName: [NSString stringWithFormat:@"Store Detail / %@ / %llu", [self.store storeName], [self.store storeid]] action: nil];
    [SCWebTracking sendTrackingEvent:te];
}

- (IBAction)callStore:(id)sender
{
    NSString *strippedPhoneNumber = [[self.store.phone componentsSeparatedByCharactersInSet:[[NSCharacterSet decimalDigitCharacterSet] invertedSet]] componentsJoinedByString:@""];
    NSString *telLink = [@"tel://" stringByAppendingString:strippedPhoneNumber];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:telLink]];
}

- (IBAction)getDirections:(id)sender
{
    CLLocationCoordinate2D latlon = CLLocationCoordinate2DMake(self.store.lat, self.store.lng);
    
    MKPlacemark* place = [[MKPlacemark alloc] initWithCoordinate:latlon addressDictionary: nil];
    MKMapItem* destination = [[MKMapItem alloc] initWithPlacemark: place];
    destination.name = self.store.storeName;
    NSDictionary* options = [[NSDictionary alloc] initWithObjectsAndKeys:
                             MKLaunchOptionsDirectionsModeDriving,
                             MKLaunchOptionsDirectionsModeKey, nil];
    [MKMapItem openMapsWithItems:@[destination] launchOptions: options];
}
@end
