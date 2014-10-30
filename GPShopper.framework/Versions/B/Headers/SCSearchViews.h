//
//  SCSearchViews.h
//  schumacher
//
//  Created by kimberly on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SCTableDelegate.h"
#import "SCCollectionDelegate.h"
#import "SCMapDelegate.h"
#import "SCScrollDelegate.h"
#import "SCUrlImageView.h"

@class SearchResultList;
@class SCSearchFetcher;
@class SCSearchSpecs;
@class SCUrlImageFetcher;
@class SCSearchResultProduct;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchProductTableEntry;

/**
 Defines methods for handling events triggered by a SCSearchProductTableEntry.
 */
@protocol SCSearchProductTableEntryDelegate < NSObject >

/**
 Called when the corresponding row in the UITableView is selected.
 */
-(void)scSearchProductTableEntryWasSelected: (SCSearchProductTableEntry *)e;

@end


/**
 Basic implementation of SCTableEntry for SCSearchResultProduct instances.
 */
@interface SCSearchProductTableEntry : SCBaseTableEntry

@property (retain) SCSearchResultProduct *product;
@property (assign) id< SCSearchProductTableEntryDelegate > delegate;

@end


/**
 Base class for UITableViewCells displaying SCSerachResultProducts.
 */
@interface SCSearchProductTableViewCell : UITableViewCell

/**
 The product displayed.
 */
@property (retain) SCSearchResultProduct *product;
@end


/**
 Simple table view cell displaying a product image and name.
 */
@interface SCSearchProductStandardTableViewCell : SCSearchProductTableViewCell
{
    @protected
    IBOutlet UILabel *productNameLabel;
}

/**
 Product image view.  Manages remote image fetching.
 */
@property (retain) IBOutlet SCUrlImageView *urlImageView;


/**
 Url to be used to populate urlImageView.
 
 [product urlForImageWithinSize: <cell size x 2>] by default.
 */
-(NSString *)productImageUrl;

@end


@interface SCSearchPaginationTableViewCell : UITableViewCell

@end




@class SCSearchPaginationTableEntry;

@protocol SCSearchPaginationTableEntryDelegate < NSObject >

@optional
-(void)scSearchPaginationTableEntry: (SCSearchPaginationTableEntry *)e
                     configuredCell: (SCSearchPaginationTableViewCell *)c;

@end


@interface SCSearchPaginationTableEntry : SCBaseTableEntry

@property (assign) id<SCSearchPaginationTableEntryDelegate> delegate;

@end



@interface SCSearchProductCollectionCell : UICollectionViewCell
@property (readonly) IBOutlet UILabel *productNameLabel;
@property (readonly) IBOutlet SCUrlImageView *urlImageView;
@end

@class SCSearchProductCollectionEntry;

@protocol SCSearchProductCollectionEntryDelegate <NSObject>

@optional
-(void)scSearchProductCollectionEntryWasSelected: (SCSearchProductCollectionEntry *)e;

@end

@interface SCSearchProductCollectionEntry : SCBaseCollectionEntry
@property (retain) SCSearchResultProduct *product;
@property (assign) id<SCSearchProductCollectionEntryDelegate> delegate;
@end



@interface SCSearchPaginationCollectionCell : UICollectionViewCell
@end


@class SCSearchPaginationCollectionEntry;

@protocol SCSearchPaginationCollectionEntryDelegate <NSObject>

@optional
-(void)scSearchPaginationCollectionEntry: (SCSearchPaginationCollectionEntry *)e
                          configuredCell: (SCSearchPaginationCollectionCell *)c;

@end


@interface SCSearchPaginationCollectionEntry : SCBaseCollectionEntry
@property (assign) id<SCSearchPaginationCollectionEntryDelegate> delegate;
@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchProductMapAnnotation;

/**
 Defines methods for handling actions triggered by a SCSearchProductMapAnnotation.
 */
@protocol SCSearchProductMapAnnotationDelegate <NSObject>

/**
 Sent when the details button is tapped.
 */
-(void)scSearchProductMapAnnotationWasTapped: (SCSearchProductMapAnnotation *)a;

@end


/**
 Map annotation for SCSearchResultProduct instances.
 */
@interface SCSearchProductMapAnnotation : SCBaseMapAnnotation
@property (retain) SCSearchResultProduct *product;
@property (assign) id<SCSearchProductMapAnnotationDelegate> delegate;

/**
 Default factory function.
 */
+(SCSearchProductMapAnnotation *)newAnnotationWithProduct: (SCSearchResultProduct *)p;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchProductTileView;

@protocol SCSearchProductTileViewDelegate < NSObject >

-(void)scSearchProductTileViewWasSelected: (SCSearchProductTileView *)v;

@end

@interface SCSearchProductTileView : UIView
{
    double lastTouch;
}

@property (retain) SCSearchResultProduct *product;
@property (assign) id<SCSearchProductTileViewDelegate> delegate;

@end


/**
 Base class for SCScrollEntry implementations
 that includes a SCSearchResultProduct.
 */

@class SCSearchProductScrollEntry;

@protocol SCSearchProductScrollEntryDelegate < NSObject >

-(void)scSearchProductScrollEntryWasSelected: (SCSearchProductScrollEntry *)e;

@end

@interface SCSearchProductScrollEntry : SCBaseScrollEntry < SCSearchProductTileViewDelegate >
@property (retain) SCSearchResultProduct *product;
@property (assign) id<SCSearchProductScrollEntryDelegate> delegate;
@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface SCFilterSearchQuery : NSObject
{
    NSString *root;
    NSString *fullQuery;
    NSMutableDictionary *filters;
}

-(id)initWithFullQuery: (NSString *)s;

@property (readonly) NSString *root;
@property (readonly) NSString *fullQuery;

-(NSString *)filterValueForKey: (NSString *)s;
-(void)setFilterValue: (NSString *)v
               forKey: (NSString *)k;
-(void)removeFilterValueForKey: (NSString *)k;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchFilterView;

@protocol SCSearchFilterViewDelegate

-(void)scSearchFilterView: (SCSearchFilterView *)v
          hasPendingQuery: (NSString *)q;

@end


@interface SCSearchFilterView : UIView
{
    UITableView *tableView;
    
    SCFilterSearchQuery *currentQuery;
    SCFilterSearchQuery *pendingQuery;
    SearchResultList *currentResultList;
    int expandedSection;
    BOOL allBeforeValues;
    
    id<SCSearchFilterViewDelegate> delegate;
    UITableViewCellSelectionStyle cellSelectionStyle;
}

@property (assign) id<SCSearchFilterViewDelegate> delegate;
@property (readwrite) UITableViewCellSelectionStyle cellSelectionStyle;

-(void)setQuery: (NSString *)s;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchResultListView;
@class SCSearchResultProduct;

@protocol SCSearchTextListViewDelegate < NSObject >

-(void)scSearchTextListView: (SCSearchResultListView *)v
            selectedProduct: (SCSearchResultProduct *)p;
-(void)noResultFoundFromList;

@optional
-(UITableViewCell *)scSearchTextListView: (SCSearchResultListView *)v
                          cellForProduct: (SCSearchResultProduct *)p;

@end

@interface SCSearchResultListView : UIView
{
    UITableView *tableView;
    NSString *query;
    NSString *zipcode;
    NSArray *grpids;
    uint64_t radius;
    SearchResultList *currentResultList;
    NSArray *products;
    SCSearchFetcher *searchFetcher;
    id<SCSearchTextListViewDelegate> delegate;
    UITableViewCellSelectionStyle cellSelectionStyle;
    BOOL isSearching;
    BOOL isFetching;
}

@property (retain) NSString *zipcode;
@property (retain) NSString *query;
@property (readwrite) uint64_t radius;
@property (assign) id<SCSearchTextListViewDelegate> delegate;
@property (readwrite) UITableViewCellSelectionStyle cellSelectionStyle;
@property (assign) BOOL isSearching; 


-(void)setTableViewColor:(UIColor *)color;
-(void)setRowHeight: (double)h;
-(void)setQuery:(NSString *)s setZipcode:(NSString *)z;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCBaseProduct;
@class SCUrlImageView;

@interface SCBaseProductIBTableViewCell : UITableViewCell
{
    IBOutlet SCUrlImageView *urlImageView;
    IBOutlet UILabel *productNameLabel;
    
    SCBaseProduct *product;
}

@property (retain) SCBaseProduct *product;

-(void)setImageUrl: (NSString *)u;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@class SCSearchResultsTableView;

@protocol SCSearchResultsTableViewDelegate

-(UITableViewCell *)scSearchResultsTableView: (SCSearchResultsTableView *)v
                              cellForProduct: (SCSearchResultProduct *)p;

-(void)scSearchResultsTableView: (SCSearchResultsTableView *)v
          configureDequeuedCell: (UITableViewCell *)c
                     forProduct: (SCSearchResultProduct *)p;

-(void)scSearchResultsTableView: (SCSearchResultsTableView *)v
                selectedProduct: (SCSearchResultProduct *)p;

@end

@interface SCSearchResultsTableView : UIView
{
    UITableView *tableView;
    SCSearchSpecs *searchSpecs;
    SCSearchFetcher *searchFetcher;
    SearchResultList *searchResults;
    NSString *dequeueIdentifier;
    int rowHeight;
    id<SCSearchResultsTableViewDelegate> delegate;
}

@property (retain) SCSearchSpecs *searchSpecs;
@property (copy) NSString *dequeueIdentifier;
@property (assign) id<SCSearchResultsTableViewDelegate> delegate;
@property (readwrite) int rowHeight;
@property (readwrite) UITableViewCellSeparatorStyle separatorStyle;

-(void)setSearchResultList: (SearchResultList *)l;
-(SearchResultList *)searchResultList;

-(void)setContentOffset: (CGPoint)p;
-(void)setBackgroundColor:(UIColor *)backgroundColor;
//-(void)setRowHeight: (int)h;

@end