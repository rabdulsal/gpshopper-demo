//
//  SCStoreLocatorViewController.h
//  EXPproject
//
//  Created by kimberly on 6/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import "SCTableDelegate.h"
#import "SCMapDelegate.h"
#import "SCLocationListView.h"
#import "SCSearchViews.h"
#import "SearchResult.h"
#import "ProductInfo.h"
#import "Location.h"
#import "SCPopup.h"

@class SCSearchSpecs;
@class SCSearchFetcher;
@class SearchResultList;
@class SCSearchResultProduct;
@class SCGeoLocation;


@class SCStoreDataTableEntry;

@protocol SCStoreDataTableEntryDelegate <NSObject>

-(void)scStoreDataTableEntryWasSelected: (SCStoreDataTableEntry *)e;

@end

@interface SCStoreDataTableEntry : SCBaseTableEntry

@property (retain) id<StoreData> store;
@property (retain) CLLocation *location;
@property (assign) id<SCStoreDataTableEntryDelegate> delegate;

@end


@interface SCStoreDataTableViewCell : UITableViewCell

@property (retain, nonatomic) id<StoreData> store;
@property (retain, nonatomic) CLLocation *location;

@property (readonly) IBOutlet UILabel *storeNameLabel;
@property (readonly) IBOutlet UILabel *streetAddressLabel;
@property (readonly) IBOutlet UILabel *cityStateLabel;
@property (readonly) IBOutlet UILabel *distanceLabel;

-(void)reloadData;

-(NSString *)distanceText;
-(NSString *)cityStateText;
-(NSString *)storeNameText;

@end


enum SCStoreLocatorStorePresentation
{
    SCStoreLocatorStorePresentationList=1,
    SCStoreLocatorStorePresentationMap=2
};

enum SCStoreLocatorInteractionMode
{
    SCStoreLocatorInteractionModeLocationSelect=1,
    SCStoreLocatorInteractionModeStores=2
};


/**
 Demo class used by SCStoreLocatorViewController.
 
 @warning Do not subclass this class.  Subclass SCSearchProductTableEntry instead.
 */
@interface SCDemoStoreTableEntry : SCSearchProductTableEntry
@end


/**
 Demo class used by SCStoreLocatorViewController.
 
 @warning Do not subclass this class.  Subclass UITableViewCell instead.
 */
@interface SCDemoStoreTableCell : UITableViewCell
@property (retain) IBOutlet UILabel *streetLabel;
@end


/**
 Comprises three main elements:
 
 - Map of store locations in an area.
 - List of store locations in an area.
 - List of major cities, at which one can look up stores.
 
 Store location lookup is implemented as a search,
 typically for the special keyword 'store_location'.
 
 ## Customization Guide ##
 
 This class is designed for flexible customization.
 
 1. Create a subclass XYZStoreViewController.h/m/xib.
 2. Add new IBOutlets to header and xib, if needed (see 'Controls' below).
 3. Create custom implementation of some of the documented methods below.
 
 ### Store Map ###
 To change individual pins on the map, subclass SCSearchProductMapAnnotation
 and override newMapAnnotationForSearchProduct:.
 
 ### Store List ###
 By default, stores are listed in a single table section
 ordered by distance.
 
 To change the presentation of individual elements in the list,
 create a subclass of SCSearchProductTableEntry, a corresponding xib file,
 and override newTableEntryForSearchProduct:.
 
 To change the organization of the table (create more than one section,
 reorder products, etc.), override newTableSectionsFromSearchResultList:.
 
 ### Controls (buttons, etc.) ###
 
 This class and its xib provide a default implementation of the following
 interface elements:
 
 - Toggling store display type (map vs. list).
   - default control: [[self navigationItem] rightBarButtonItem]
   - method to override: setStorePresentationControlHidden:presentation:
 - GPS lookup
   - default control: detectLocationButton
   - calls: detectLocation:
   - method to override: setDetectLocationControlHidden:
 - Dismiss city lookup
   - default control: closeLocationSelectButton
   - calls: closeLocationSelect:
   - method to override: setLocationSelectCloseControlHidden:
 
 To make these features available with different UI controls,
 subclass this view controller and add IBOutlets for it for the new controls.
 Then override the appropriate method to update the new control's
 visibility as needed.
 */

@interface SCStoreLocatorViewController : UIViewController < SCSearchProductTableEntryDelegate,
                                                              SCSearchProductMapAnnotationDelegate,
                                                              SCLocationTableEntryDelegate >
{
    @protected
    
    IBOutlet UITextField *textField;
    IBOutlet UIView *textFieldAccessoryView;
    IBOutlet UITableView *storeTableView;
    IBOutlet UITableView *cityTableView;
    IBOutlet UIView *loadingPopupView;
    IBOutlet MKMapView *mapView;
    
    IBOutlet UIButton *closeLocationSelectButton;
    IBOutlet UIButton *detectLocationButton;
    
    IBOutlet UIView *loadingView;
    
    SearchResultList *searchResults;
    SCSearchFetcher *searchFetcher;
    
    SCGeoLocation *geolocation;
    
    // view data
    SCTableDelegate *storeTableDelegate;
    SCLocationTableDelegate *cityTableDelegate;
    SCMapDelegate *mapDelegate;
    SCPopup *loadingPopup;

    NSArray *mapAnnotations;
    
    // state
    BOOL searchInProgress;
    enum SCStoreLocatorInteractionMode interactionMode;
    enum SCStoreLocatorStorePresentation storePresentation;
}

/** @name Properties */

/**
 Initial search specs.  Zipcode may change.
 */
@property (readonly) SCSearchSpecs *searchSpecs;

/**
 Geolocation used by 'detect location' feature.
 */
@property (retain) SCGeoLocation *geolocation;

/**
 The query used for store locations.  Typically 'store_location'.
 */
@property (copy) NSString *searchQuery;

/**
 Constrant about store location search results.
 */
@property (retain) SCSearchConstraint *searchConstraint;

/**
 The zipcode currently being used for store lookup.

 Updated in response to changes in geolocation and to location select.
 
 Either currentZipcode will be non-nil or currentLatlon will be a valid coordinate,
 but not both at once.
 */
@property (readonly) NSString *currentZipcode;

/**
 The latlon currently being used for store lookup.
 
 See discussion of currentZipcode.
 */
@property (readonly) CLLocationCoordinate2D currentLatlon;

/**
 The results of the most recent search.
 */
@property (readonly) SearchResultList *searchResults;

/**
 The best match for the location text user entered,
 evaluated against a fixed list of locations.
 
 For example, "chiasdf" would match locations named "Chicago"
 */
@property (readonly) SCLocationListSubstringMatch *locationSubstringMatch;

/**
 Generates search specs based on current settings
 and triggers a new search if need be.
 
 Called when any of the following are changed:
 
 * geolocation
 * searchQuery
 * searchConstraint
 * currentZipcode
 * currentLatlon
 */
-(void)updateSearchSpecs;

/**
 Displayed to a user in a UIAlertView when location detection fails.
 
 If in the future more control over this feature is needed,
 create public method 'presentLocationDetectionFailure'.
 */
@property (copy) NSString *locationDetectionFailureMessage;

/**
 Part of store location proccess currently visible.
 
 - Selecting a location
 - Viewing stores
 
 @important Provided as a readwrite property for use in custom UI control functions.
 */
@property (readwrite) enum SCStoreLocatorInteractionMode interactionMode;

/**
 How stores are presented to the user (map vs. list).
 
 @important Provided as a readwrite property for use in custom UI control functions.
 */
@property (readwrite) enum SCStoreLocatorStorePresentation storePresentation;

/** @name Actions */

/**
 Switch store presentation from list to map and vice versa.
 */
-(IBAction)toggleStorePresentation: (id)sender;

/**
 Dismiss the keyboard associated with the textField.
 */
-(IBAction)closeKeyboard: (id)sender;

/**
 Switch to 'view stores' interaction mode.
 */
-(IBAction)closeLocationSelect:(id)sender;

/**
 Trigger GPS location detection.
 
 On successful gps lookup, new store search will be done automatically.
 */
-(IBAction)detectLocation:(id)sender;

/** @name Loading */

-(void)showLoadingIndicator;

-(void)hideLoadingIndicator;

/**
 Generic constructor for a SCPopup instance to show a loading indicator.
 
 By default, calls newAlertStyleLoadingPopup.
 
 Used in default implementation of showLoadingIndicator.
 */
-(SCPopup *)newLoadingPopup;

/**
 Constructor for an alert-style loading popup.
 
 Used in default implementation of newLoadingPopup.
 */
-(SCAlertStylePopup *)newAlertStyleLoadingPopup;

/** @name Event callbacks */

/**
 Called when searchResults has been updated following a remote search call.
 
 @param l The new value for searchResults.
 */
-(void)searchResultsWereUpdated: (SearchResultList *)l;

/**
 Called during free text input by the user.
 
 Whenever the best match changes, locationSubstringMatch is updated
 and this method is called.
 */
-(void)locationSubstringMatchWasUpdated: (SCLocationListSubstringMatch *)m;

/** @name Configure controls UI */

/**
 By default, manages a UISegmentedControl instance storePresentationSegmentedControl.
 
 Override to replace with some other control
 (UIBarButtonItem in UINavigationItem, for example).
 */
-(void)setStorePresentationControlHidden: (BOOL)h
                            presentation: (enum SCStoreLocatorStorePresentation )p;

/**
 By default, manages a UIButton instance closeLocationSelectButton.
 
 Override to replace with some other control (ex. UIBarButtonItem).
 */
-(void)setLocationSelectCloseControlHidden: (BOOL)h;

/**
 By default, manages a UIButton instance detectLocationButton.
 
 Override to replace with some other control (ex. UIBarButtonItem).
 */
-(void)setDetectLocationControlHidden: (BOOL)h;

/** @name Configure location list UI */

/**
 Used to configure free text location input.
 
 Override to constraint to locations matching the list,
 or zipcodes only (five digit strings), etc.
 */
-(BOOL)shouldAllowLocationString: (NSString *)s;

/** @name Configure store map UI */

/**
 Generates a single store map annotation.
 
 Called by standard implementation of newMapAnnotationsFromSearchResultList:
 
 Override for small changes to store map UI (ex: using a different pin image).
 */
-(id<SCMapAnnotation>)newMapAnnotationForSearchProduct: (SCSearchResultProduct *)p;

/**
 Generates all the store map annotations.
 
 Override for changes to store map UI that cannot be achieved 
 by overriding newMapAnnotationForSearchProduct:.
 
 @warning Overriding this function will prevent newMapAnnotationForSearchProduct:
 from being called unless it is in the implementation of this function.
 */
-(NSArray *)newMapAnnotationsFromSearchResultList: (SearchResultList *)l;

/**
 Displays annotations in map view.
 
 By default, just calls addAnnotations.
 
 Override to do things like select the first annotation.
 */
-(void)updateMapViewWithAnnotations: (NSArray *)as;

/**
 Region for mapView.
 */
-(MKCoordinateRegion)regionForAnnotations: (NSArray *)as
                            defaultRegion: (MKCoordinateRegion)r;


/** @name Configure store list UI */

/**
 Generates a single store table entry.
 
 Called by standard implementation of newTableSectionsFromSearchResultList:
 
 Override for small changes to store list UI (ex: using a different xib).
 */
-(id<SCTableEntry>)newTableEntryForSearchProduct: (SCSearchResultProduct *)p;


/**
 Generates all the store table sections.
 
 Override for changes to store table UI that cannot be achieved
 by overriding newTableEntryForSearchProduct: (ex: grouping stores
 into sections by type).
 
 @warning Overriding this function will prevent newTableEntryForSearchProduct:
 from being called unless it is in the implementation of this function.
 */
-(NSArray *)newTableSectionsFromSearchResultList: (SearchResultList *)l;


/** @name Handle store selection */

-(void)gotoStoreInfoPageForProduct: (SCSearchResultProduct *)p;

@end


@class PhoneCallPath;
@class SCStoreDataMapView;

/**
 Displays information about a single store location.
 
 This view controller's UI can be tweaked largely
 by creating a custom xib file.
 
 Subclass if additional functionality is needed
 (check-in button, for example).
 */
@interface SCStoreInfoViewController : UIViewController
{
    IBOutlet UILabel *nameLabel;
    IBOutlet UILabel *subnameLabel;
    IBOutlet UILabel *streetAddrLabel;
    IBOutlet UILabel *cityStateLabel;
    IBOutlet UILabel *hoursLabel;
    IBOutlet MKMapView *mapView;
    
    PhoneCallPath *phoneCallPath;
}

/**
 The store data to be displayed.
 */
@property (retain) id<StoreData> storeData;

/**
 The delegate of the map view.
 */
@property (retain) SCMapDelegate *mapDelegate;

/**
 NSDictionary with launchOptions to be used by the MKMap openMapWithLatLon: call.
 */
@property (retain) NSDictionary *mapLaunchOptions;


/** @name User actions */

/**
 Make a phone call from the device to the store's phone number.
 */
-(IBAction)callStore:(id)sender;

/**
 Show interactive map.  By default, opens up Maps application.
 */
-(IBAction)openMap:(id)sender;

/** @name UI */

/**
 Refreshes UI elements using the latest data.
 
 Triggered on viewDidLoad and setStoreData:
 */
-(void)updateUI;

/**
 Returns 'pin' image used to indicate store location in map.
 
 Subclass to customize.
 */
-(UIImage *)annotationImageForStoreData: (id<StoreData>)s;

@end

