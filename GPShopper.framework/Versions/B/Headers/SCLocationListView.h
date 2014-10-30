//
//  SCLocationListView.h
//  schumacher
//
//  Created by kimberly on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SCTableDelegate.h"

@class SCLocationList;
@class SCLocationListView;
@class Location;
@class SCLocationSearchResult;


@class SCLocationTableEntry;

@protocol SCLocationTableEntryDelegate <NSObject>

-(void)scLocationTableEntryWasSelected: (SCLocationTableEntry *)e;

@end

@interface SCLocationTableEntry : SCBaseTableEntry
@property (retain) Location *location;
@property (assign) id<SCLocationTableEntryDelegate> delegate;
@end

/**
 Populates a UITableView
 from a SCLocationList.
 
 This class supports filtering by an initial fragment
 of either a city name ("New Yo") or a zip code ("100").
 See properties initialFilter and filteredLocations
 for details.
 */

@interface SCLocationTableDelegate : SCTableDelegate

/**
 List of locations.
 */
@property (retain) SCLocationList *locationList;

/**
 Delegate for the table entries.
 */
@property (assign) id<SCLocationTableEntryDelegate> entryDelegate;

/** @name Filtering */

/**
 Array of Location instances from locationList
 which match initialFilter.
 */
@property (readonly) NSArray *filteredLocations;

/**
 Current initial fragment.
 
 On setting this property, the table sections are repopulated
 with only those Location objects which match this fragment.
 
 Matching is case-insensitive.
 */
@property (copy) NSString *initialFilter;


/** @name UI configuration */

/**
 Header title for table section listing cities in alphabetical order.
 */
@property (copy) NSString *citySectionTitle;

/**
 Header title for table section listing cities in numerical order by zip code.
 */
@property (copy) NSString *zipSectionTitle;

/**
 Table entry factory function.  Override to customize.
 */
-(id<SCTableEntry>)newEntryFromLocation: (Location *)l;

/**
 Generates a UI-friendly string representation of a Location instance.
 */
-(NSString *)stringFromLocation: (Location *)l;

@end



/**
 DEPRECATED.  Use SCLocationTableDelegate instead.
 */
@interface SCLocationListViewSection : NSObject
{
    int sortType;
    NSString *title;
}

@property (readonly) int sortType;
@property (readonly) NSString *title;

-(id)initWithSortType: (int)s
                title: (NSString *)t;

@end


@protocol SCLocationListViewDelegate

-(void)scLocationListView: (SCLocationListView *)v
         selectedLocation: (Location *)l;

@end

/**
 DEPRECATED.  Use SCLocationTableDelegate instead.
 */
@interface SCLocationListView : UIView
{
    UITableView *tableView;
    SCLocationList *locationList;
    NSMutableArray *sections;
    id<SCLocationListViewDelegate> delegate;
    UITableViewCellSelectionStyle cellSelectionStyle;
}

@property (assign) id<SCLocationListViewDelegate> delegate;
@property (retain) SCLocationList *locationList;
@property (readwrite) UITableViewCellSelectionStyle cellSelectionStyle;


-(void)scrollToString: (NSString *)s;

-(void)addSectionOfSortType: (int)s
                      title: (NSString *)t;

-(NSString *)zipFromSearch:(NSString *)searchString;

@end
