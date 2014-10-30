//
//  SCDomainUI.h
//  feature
//
//  Created by kimberly on 9/11/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SCCollectionDelegate.h"
#import "SCTableDelegate.h"
#import "SCDomain.h"
#import "SCUrlImageView.h"
#import "SCUrlImageScrollView.h"


@class SCDomainValueCollectionEntry;


/**
 Event callbacks for SCDomainValueCollectionEntry.
 */
@protocol SCDomainValueCollectionEntryDelegate

/**
 */
-(void)scDomainValueCollectionEntryWasSelected: (SCDomainValueCollectionEntry *)e;

@end


@protocol SCDomainValueUIEntry <NSObject>

/**
 The name of the domain in which domainValue lives.
 */
-(NSString *)domainName;

/**
 The domain value being displayed.
 */
-(SCDomainValue *)domainValue;

/**
 Whether the value can be selected.
 */
-(BOOL)selectable;

/**
 Whether the value is currently selected.
 */
-(BOOL)selected;

@end


/**
 SCCollectionEntry implementation that displays a SCDomainValue instance.
 
 ### See also ###
 
 * SCDomainValue
 * SCDomainValueCollectionEntryDelegate
 * SCDomainValueCollectionCell
 */
@interface SCDomainValueCollectionEntry : SCBaseCollectionEntry < SCDomainValueUIEntry >

@property (copy) NSString *domainName;
@property (retain) SCDomainValue *domainValue;
@property (readwrite) BOOL selectable;
@property (readwrite) BOOL selected;

/**
 Delegate to receive event callbacks.
 */
@property (assign) id<SCDomainValueCollectionEntryDelegate> delegate;

+(SCDomainValueCollectionEntry *)newDefaultCollectionEntryForDomainValue: (SCDomainValue *)v;

@end


/**
 UICollectionViewCell displaying a SCDomainValue.
 
 ### See also ###
 
 * SCDomainValue
 * SCDomainValueCollectionEntry
 */
@interface SCDomainValueCollectionCell : UICollectionViewCell

@property (readonly) IBOutlet UIView *unselectableOverlayView;

/**
 Image displaying the value's swatch, if it exists.
 */
@property (readonly) IBOutlet SCUrlImageView *urlImageView;

/**
 Label displaying the value's name.
 */
@property (readonly) IBOutlet UILabel *label;

@property (retain, nonatomic) SCDomainValue *domainValue;
@property (readwrite, nonatomic) BOOL domainValueIsSelectable;
@property (readwrite, nonatomic) BOOL domainValueIsSelected;

/**
 Updates UI elements from domainValue, domainValueIsSelectable, and domainValueIsSelected.
 
 Override to customize.
 */
-(void)reloadData;

@end


@class SCDomainValueImagesCollectionEntry;

@protocol SCDomainValueImagesCollectionEntryDelegate <NSObject>

@optional

-(void)scDomainValueImagesCollectionEntry: (SCDomainValueImagesCollectionEntry *)e
                         selectedNthImage: (NSUInteger)n;

@end

/**
 SCCollectionEntry which specifies an array in a SCDomainValue's supplemental
 to be interpreted as image urls.
 
 ### See also ###
 
 * SCDomainValue
 * SCDomainValueCollectionEntry
 */
@interface SCDomainValueImagesCollectionEntry : SCBaseCollectionEntry < SCUrlImageScrollViewDelegate >

@property (assign) id<SCDomainValueImagesCollectionEntryDelegate> delegate;

/**
 The domain value whose supplemental data contains image urls.
 */
@property (retain) SCDomainValue *domainValue;

/**
 The key for the array of image urls (ex. "product_images")
 */
@property (copy) NSString *valueSupplementalKey;
@end


@interface SCDomainValueImagesCollectionCell : UICollectionViewCell
@property (readonly) IBOutlet SCUrlImageScrollView *urlImageScrollView;
-(IBAction)selectCurrentImage:(id)sender;
@end


@interface SCDomainCollectionSupplement : SCBaseCollectionSupplement
@property (retain) SCDomain *domain;
@end


@interface SCDomainCollectionSupplementalView : UICollectionReusableView
@property (readonly) IBOutlet UILabel *domainNameLabel;
@end


@class SCDomainTableHeaderView;

@protocol SCDomainTableHeaderViewDelegate <NSObject>

@optional
-(void)scDomainTableHeaderViewSelectedAll: (SCDomainTableHeaderView *)v;
-(void)scDomainTableHeaderViewSelectedNone: (SCDomainTableHeaderView *)v;

@end

@interface SCDomainTableHeaderView : UIView

@property (assign) id<SCDomainTableHeaderViewDelegate> delegate;

@property (copy) NSString *domainName;
@property (readonly) IBOutlet UILabel *domainNameLabel;
-(IBAction)selectAll: (id)sender;
-(IBAction)selectNone: (id)sender;

@end


@class SCDomainValueTableEntry;

@protocol SCDomainValueTableEntryDelegate <NSObject>

-(void)scDomainValueTableEntryWasSelected: (SCDomainValueTableEntry *)e;

@end

@interface SCDomainValueTableEntry : SCBaseTableEntry < SCDomainValueUIEntry >

@property (copy) NSString *domainName;
@property (retain) SCDomainValue *domainValue;
@property (readwrite) BOOL selectable;
@property (readwrite) BOOL selected;
@property (assign) id<SCDomainValueTableEntryDelegate> delegate;

@end


@interface SCDomainValueTableViewCell : UITableViewCell

@property (readonly) IBOutlet UILabel *domainValueLabel;
@property (readonly) IBOutlet UIImageView *selectedImageView;

@end


@interface SCDomainTableSection : SCBaseTableSection

@property (retain) SCDomain *domain;
@property (copy) NSString *displayedDomainName;
@property (assign) id<SCDomainTableHeaderViewDelegate> headerDelegate;

@end