//
//  GPDStoresViewController.m
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDStoresViewController.h"
#import "GPDStoreDetailViewController.h"
#import "GPDAppDelegate.h"



@interface GPDStoresViewController ()

@property (strong, nonatomic) NSArray *stores;
@property (strong, nonatomic) GPSSDKStoreLocator *storeFetcher;
@property (strong, nonatomic) IBOutlet UIButton *toggleButton;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinner;

/* ---------------- RASHAD EDITS ----------------------- */
@property SCGeoLocation *userLocation;
@property NSString *storeDistance;
/* ---------------------------------------------------- */
- (IBAction)cancelSearch:(id)sender;

@end

@implementation GPDStoresViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.storeFetcher = [GPSSDKStoreLocator defaultInstance];
    
    self.listView.hidden = (self.viewMode != GPDStoresListMode);
    [self.searchBar setInputAccessoryView:self.toolBar];
    UIBarButtonItem *toggleButton = [[UIBarButtonItem alloc] initWithCustomView:self.toggleButton];

    UIBarButtonItem *locateButton = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"locate"]
                                                                     style:UIBarButtonItemStylePlain
                                                                    target:self
                                                                    action:@selector(searchCurrentLocation)];
    
    [self.navigationItem setRightBarButtonItems:@[toggleButton, locateButton]];
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(reactToStoreLocationFetchedNotification:)
     name:kGPSSDKStoreLocationFetchedNotification
     object:nil];
    
    /* --------------RASHAD EDITS-------------------------------- */
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(currentLocation:) name:@"locationUpdated" object:nil];
    /* ---------------------------------------------------- */
    [self searchCurrentLocation];
}

- (void)setViewMode:(GPDStoresMode)viewMode
{
    [self.toggleButton setImage:[UIImage imageNamed:(viewMode == GPDStoresListMode) ? @"map" : @"list"]
                       forState:UIControlStateNormal];
    
    [UIView transitionWithView:self.containerView
                      duration:0.4
                       options:UIViewAnimationOptionTransitionFlipFromLeft
                    animations:^{
                        self.listView.hidden = (viewMode != GPDStoresListMode);
                    } completion:nil];
    _viewMode = viewMode;
}

- (IBAction)toggleMapListViews
{
    self.viewMode = !self.viewMode;
}

- (void)searchCurrentLocation
{
    [self.storeFetcher fetchForCurrentLocation];
    [self.spinner startAnimating];
}

- (void)currentLocation:(NSNotification *)notification
{
    self.userLocation = (SCGeoLocation *)[[notification userInfo] valueForKey:@"currentLocation"];
    NSLog(@"Current User Location: %lf, %lf", self.userLocation.latlon.latitude, self.userLocation.latlon.longitude);
}

- (void)showDetailForStore:(id<StoreData>)store
{
    GPDStoreDetailViewController *vc = [GPDStoreDetailViewController new];
    vc.store = store;
    
    /* -----------------RASHAD EDITS -------------------- */
    _storeDistance = [self getDistanceFrom:_userLocation toStoreLocation:store.lat longitude:store.lng];
    vc.storeDistance = _storeDistance;
    /* ---------------------------------------------------- */
    [self.navigationController pushViewController:vc animated:YES];
}

- (IBAction)cancelSearch:(id)sender {
    [self.searchBar resignFirstResponder];
}

#pragma mark MKMapViewDelegate

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view
{

}

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control
{
    GPDStoreAnnotation *annotation = (GPDStoreAnnotation *)view.annotation;
    id<StoreData> store = annotation.store;
    [self showDetailForStore:store];
}

- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation
{
    MKPinAnnotationView *pin;
    if ([annotation isKindOfClass:[GPDStoreAnnotation class]]) {
        static NSString *reuseID = @"com.gpshopper.storePin";
        pin = (MKPinAnnotationView *)[mapView dequeueReusableAnnotationViewWithIdentifier:reuseID];
        if (!pin) {
            pin = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:reuseID];
            pin.canShowCallout = YES;
            pin.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
        }
    }
    return pin;
}

#pragma mark UISearchBarDelegate

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    [searchBar resignFirstResponder];
    NSString *text = searchBar.text;
    
    
    NSCharacterSet *set = [NSCharacterSet characterSetWithCharactersInString:text];
    BOOL isZipcode = ([[NSCharacterSet decimalDigitCharacterSet] isSupersetOfSet:set] && text.length==5);
    
    if (isZipcode) {
        [self.storeFetcher fetchForZipCode:text];
    } else {
        CLGeocoder *geocoder = [CLGeocoder new];
        [geocoder geocodeAddressString:text completionHandler:^(NSArray *placemarks, NSError *error) {
            CLPlacemark *bestMatch = [placemarks firstObject];
            if (CLLocationCoordinate2DIsValid(bestMatch.location.coordinate)) {
                [self.storeFetcher fetchForCoordinates:bestMatch.location.coordinate];
            } else {
                [self.spinner stopAnimating];
            }
        }];
    }
    
    [self.spinner startAnimating];
}


#pragma mark NSNotificationCenter

- (void)reactToStoreLocationFetchedNotification:(NSNotification *)sender
{
    if (!self.view.window) {
        return;
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.spinner stopAnimating];
    });
    self.stores = [self.storeFetcher.stores copy];
    if (self.stores.count) {
        [self.listView reloadData];
        [self reloadAnnotations];
    } else {
        [[[UIAlertView alloc] initWithTitle:@"No Stores Found"
                                    message:@""
                                   delegate:nil
                          cancelButtonTitle:@"Okay"
                          otherButtonTitles:nil] show];
    }
}

- (void)reloadAnnotations
{
    [self.mapView removeAnnotations:self.mapView.annotations];
    
    NSMutableArray *annotations = [NSMutableArray array];
    for (id<StoreData> store in self.stores) {
        GPDStoreAnnotation *annotation = [GPDStoreAnnotation new];
        annotation.store = store;
        [annotations addObject:annotation];
    }
    [self.mapView addAnnotations:annotations];
    [self.mapView showAnnotations:annotations animated:YES];

}

#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.stores.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *reuseID = @"storeCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseID];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:reuseID];
        cell.detailTextLabel.textColor = [UIColor lightGrayColor];
    }
    id<StoreData> store = self.stores[indexPath.row];
    cell.textLabel.text = store.storeName;
    
    /* ----------------RASHAD EDITS ------------------------------------ */
     _storeDistance = [self getDistanceFrom:_userLocation toStoreLocation:store.lat longitude:store.lng];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@ (%@ miles away)",store.streetAddress, _storeDistance];
    /* ---------------------------------------------------- */
    return cell;
}

/* ----------------RASHAD EDITS ------------------------------------ */

- (NSString *)getDistanceFrom:(SCGeoLocation *)userLocation toStoreLocation:(CGFloat)storeLatitude longitude:(CGFloat)storeLongitude
{
    CLLocation *userLocale = [[CLLocation alloc] initWithLatitude:userLocation.lat longitude:userLocation.lon];
    
    CLLocation *storeLocale = [[CLLocation alloc] initWithLatitude:storeLatitude longitude:storeLongitude];
    
    CLLocationDistance distance = [userLocale distanceFromLocation:storeLocale]*0.000621371;
    
    return [NSString stringWithFormat:@"%0.2f", distance];
}

/* ----------------END------------------------------------ */

#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    id<StoreData> store = self.stores[indexPath.row];
    [self showDetailForStore:store];
}




@end
